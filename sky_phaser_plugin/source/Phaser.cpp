
namespace sky_phaser {
    
    void Phaser::prepare(double sr, int expectedMaxFramesPerBlock) {
        juce::ignoreUnused(expectedMaxFramesPerBlock);
        sampleRate = static_cast<float>(sr);
        // need sampleRate to be set to set these defaults
        setRange(440.f, 1600.f);
        setModulationRate(.5f);
    }

    void Phaser::process(juce::AudioBuffer<float>& buffer) noexcept {

        updateFeedback();
        updateModulationDepth();

        // for each frame
        for (const auto frameIndex : std::views::iota(0, buffer.getNumSamples())) {
            // for each channel sample in the frame
            for (const auto channelIndex :
                std::views::iota(0, buffer.getNumChannels())) {
                const auto inputSample = buffer.getSample(channelIndex, frameIndex);                
                const auto outputSample = update(inputSample);
                buffer.setSample(channelIndex, frameIndex, outputSample);
            }
        }
    }

    void Phaser::setRange(float fMin, float fMax) { // Hz
        dmin = fMin / (sampleRate / 2.f);
        dmax = fMax / (sampleRate / 2.f);
    }

    void Phaser::setModulationRate(float rate) { // cps
        lfoInc = 2.f * juce::MathConstants<float>::pi * (rate / sampleRate);
    }

    void Phaser::setFeedback(float fb) {
        currentFeedback = fb;
    }

    void Phaser::updateFeedback() {
        if (currentFeedback != feedbackToSet) {
            // modulationDepthSmoothed.setCurrentAndTargetValue(getNextModulationDepthValue());
            currentFeedback = feedbackToSet;
            // modulationDepthSmoothed.setTargetValue(getNextModulationDepthValue());
        }
    }

    float Phaser::getNextFeedbackValue() {
        //if (modulationDepthSmoothed.isSmoothing()) {
        //    return modulationDepthSmoothed.getNextValue();
        //}
        return currentFeedback;
    }

    void Phaser::setModulationDepth(float modDepth) {
        modulationDepthToSet = modDepth;
    }

    void Phaser::updateModulationDepth() {
        if (currentModulationDepth != modulationDepthToSet) {
            // modulationDepthSmoothed.setCurrentAndTargetValue(getNextModulationDepthValue());
            currentModulationDepth = modulationDepthToSet;
            // modulationDepthSmoothed.setTargetValue(getNextModulationDepthValue());
        }
    }

    float Phaser::getNextModulationDepthValue() {
        //if (modulationDepthSmoothed.isSmoothing()) {
        //    return modulationDepthSmoothed.getNextValue();
        //}
        return currentModulationDepth;
    }

    float Phaser::update(float inSamp) {
        //calculate and update phaser sweep lfo...
        float d = dmin + (dmax - dmin) * ((sin(lfoPhase) + 1.f) / 2.f);
        lfoPhase += lfoInc;
        if (lfoPhase >= juce::MathConstants<float>::pi * 2.f) {
            lfoPhase -= juce::MathConstants<float>::pi * 2.f;
        }        

        for (auto& e : allPassDelays) {
            e.Delay(d);
        }
        
        auto y = std::accumulate(std::next(allPassDelays.rbegin()), allPassDelays.rend(),
            allPassDelays.back().Update(inSamp + zm1 * getNextFeedbackValue()), [](auto acc, auto& e) { return e.Update(acc); });
        zm1 = y;

        return inSamp + y * getNextModulationDepthValue();
    }

   


}