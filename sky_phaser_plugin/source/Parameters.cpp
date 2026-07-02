
namespace sky_phaser {
	namespace {
		auto& addParameterToProcessor(juce::AudioProcessor& processor, auto parameter) {
			auto& result = *parameter;
			processor.addParameter(parameter.release());
			return result;
		}
	}

	juce::AudioParameterFloat& createModulationRateParameter(juce::AudioProcessor& processor) {

		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterFloat>(
				juce::ParameterID{ "modulation.rate", Parameters::versionHint },
				"Modulation Rate",
				juce::NormalisableRange<float>{ .1f, 20.f, .01f, .4f },
				10.f,
				juce::AudioParameterFloatAttributes{}.withLabel("Hz")));

	}

	juce::AudioParameterFloat& createModulationDepthParameter(juce::AudioProcessor& processor) {

		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterFloat>(
				juce::ParameterID{ "modulation.depth", Parameters::versionHint },
				"Modulation Depth",
				juce::NormalisableRange<float>{ 0.f, 1.f, .01f },
				0.4f,
				juce::AudioParameterFloatAttributes{}.withLabel("Depth")));

	}

	juce::AudioParameterFloat& createFeedbackParameter (
		juce::AudioProcessor& processor) {
		constexpr auto versionHint = 1;
		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterFloat>(
				juce::ParameterID{ "feedback.value", versionHint }, "Feedback",
				juce::NormalisableRange<float>{0.01f, 0.99f, 0.01f},
				0.7f,
				juce::AudioParameterFloatAttributes{}.withLabel("fb")));
	}

	juce::AudioParameterBool& createBypassParameter(juce::AudioProcessor& processor) {

		return addParameterToProcessor(
			processor,
			std::make_unique<juce::AudioParameterBool>(
				juce::ParameterID{ "bypass", Parameters::versionHint },
				"Bypass",
				false));

	}

	Parameters::Parameters(juce::AudioProcessor& processor) : 
		modulationRate{ createModulationRateParameter(processor) },
		modulationDepth{ createModulationDepthParameter(processor) },
		feedback{ createFeedbackParameter(processor) },
		bypass{ createBypassParameter(processor) }
	{}
}  // namespace sky_phaser
