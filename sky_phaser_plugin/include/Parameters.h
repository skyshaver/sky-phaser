#pragma once

namespace sky_phaser {
	struct Parameters {
		explicit Parameters(juce::AudioProcessor&);

		juce::AudioParameterFloat& modulationRate;
		
		juce::AudioParameterFloat& modulationDepth;

		juce::AudioParameterFloat& feedback;

		
		juce::AudioParameterBool& bypass;
		// juce::AudioParameterChoice& waveform;

		static constexpr int versionHint = 1;

		JUCE_DECLARE_NON_COPYABLE(Parameters)
		JUCE_DECLARE_NON_MOVEABLE(Parameters)
	};
}  // namespace tremolo
