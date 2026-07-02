
namespace sky_phaser {

	PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p) {


		background.setImage(juce::ImageCache::getFromMemory(assets::Background_png, assets::Background_pngSize));

		logo.setImage(juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));


		// Make sure that before the constructor has finished, you've set the
		// editor's size to whatever you need it to be.
		setSize(540, 270);



		

		/*addAndMakeVisible(background);
		addAndMakeVisible(logo);*/
	}

	void PluginEditor::resized() {
		const auto bounds = getLocalBounds();		
		/*logo.setBounds({ 16, 16, 105, 24 });
		background.setBounds(bounds);*/


	}
	void sky_phaser::PluginEditor::paint(juce::Graphics& g) {
		// fill the whole window white
		g.fillAll(juce::Colours::white);
		// set the current drawing colour to black
		g.setColour(juce::Colours::black);
		// set the font size and draw text to the screen
		g.setFont(15.0f);
		g.drawFittedText("DSP Testing", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
	}

	//void sky_phaser::PluginEditor::sliderValueChanged(juce::Slider* slider) {
	//	// pluginProcessor.parameterOne = parameterOne.getValue();
	//}

}  // namespace sky_phaser
