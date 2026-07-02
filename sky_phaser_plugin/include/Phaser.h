/*
    class: Phaser
    implemented by: Ross Bencina <rossb@kagi.com>
    date: 24/8/98

    Phaser is a six stage phase shifter, intended to reproduce the
    sound of a traditional analogue phaser effect.
    This implementation uses six first order all-pass filters in
    series, with delay time modulated by a sinusoidal.

    This implementation was created to be clear, not efficient.
    Obvious modifications include using a table lookup for the lfo,
    not updating the filter delay times every sample, and not
    tuning all of the filters to the same delay time.

    Thanks to:
    The nice folks on the music-dsp mailing list, including...
    Chris Towsend and Marc Lindahl

    ...and Scott Lehman's Phase Shifting page at harmony central:
    http://www.harmony-central.com/Effects/Articles/Phase_Shifting/

*/

#pragma once

namespace sky_phaser {

    class Phaser {
    
    public:
        Phaser()                                 
        {
           
        }

        void prepare(double sr, int expectedMaxFramesPerBlock);
        void process(juce::AudioBuffer<float>& buffer) noexcept;

        void setRange(float fMin, float fMax); // Hz

        void setModulationRate(float rate); // cps

        void setFeedback(float fb);  // 0 -> < 1.
        void updateFeedback();
        
        void setModulationDepth(float d);   // 0 -> 1.     
        void updateModulationDepth();

        float update(float inSamp);

        void reset() noexcept {}


    private:
        class AllPassDelay {
        public:
            AllPassDelay()
                : a1(0.f)
                , zm1(0.f)
            {
            }

            void Delay(float delay) { // sample delay time
                a1 = (1.f - delay) / (1.f + delay);
            }

            float Update(float inSamp) {
                float y = inSamp * -a1 + zm1;
                zm1 = y * a1 + inSamp;

                return y;
            }
        private:
            float a1, zm1;
        };
        
        std::array<AllPassDelay, 6> allPassDelays;

        float dmin, dmax; // range
        
        float getNextFeedbackValue();
        float currentFeedback{ 0.7f };
        float feedbackToSet = currentFeedback;

        float lfoPhase{ 0.f };        

        float lfoInc;

        float getNextModulationDepthValue();
        float currentModulationDepth{.4f};
        float modulationDepthToSet = currentModulationDepth;
        
        float sampleRate;

        float zm1{0.f};
    };

} // namespace sky_phaser