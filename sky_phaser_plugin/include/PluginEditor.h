#pragma once

namespace sky_phaser {
	class PluginEditor : public juce::AudioProcessorEditor {
	public:
		explicit PluginEditor(PluginProcessor&);

		void resized() override;
		void paint(juce::Graphics&) override;

	private:

		// PluginProcessor& pluginProcessor;
		
		

		juce::ImageComponent background;
		juce::ImageComponent logo;	

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
	};
}  // namespace sky_phaser
