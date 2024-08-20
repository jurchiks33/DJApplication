//#include "MainComponent.h"
//
////==============================================================================
//MainComponent::MainComponent()
//{
//    // Make sure you set the size of the component after
//    // you add any child components.
//    setSize (800, 600);
//
//    // Some platforms require permissions to open input channels so request that here
//    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
//        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
//    {
//        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
//                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
//    }
//    else
//    {
//        // Specify the number of input and output channels that we want to open
//        setAudioChannels (0, 2);
//    }
//    
//    addAndMakeVisible(playButton);
//    addAndMakeVisible(stopButton);
//    addAndMakeVisible(loadButton);
//    
//    addAndMakeVisible(volSlider);
//    
//    
//    playButton.addListener(this);
//    stopButton.addListener(this);
//    loadButton.addListener(this);
//    volSlider.addListener(this);
//}
//
//MainComponent::~MainComponent()
//{
//    // This shuts down the audio device and clears the audio source.
//    shutdownAudio();
//}
//
////==============================================================================
//void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
//{
//    phase = 0.0;
//    dphase = 0.0001;
//    
//    formatManager.registerBasicFormats();
////    juce::URL audioURL{"file:///home/mattew/aon_inspired.mp3"};
////    
////    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
////    if (reader != nullptr)
////    {
////        std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource (reader,
////                                                                                               true));
////        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
////        readerSource.reset(newSource.release());
////        transportSource.start();
////    }
//    
//    transportSource.prepareToPlay(
//                                  samplesPerBlockExpected,
//                                  sampleRate);
//}
//
//void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
//{
//    transportSource.getNextAudioBlock(bufferToFill);
//}
//
////void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
////{
////
////    auto* leftChan = bufferToFill.buffer->getWritePointer(0,
////                                                          bufferToFill.startSample);
////    auto* rightChan = bufferToFill.buffer->getWritePointer(0,
////                                                          bufferToFill.startSample);
////    
////    for(auto i=0; i < bufferToFill.numSamples; ++i)
////    {
////        //double sample = rand.nextDouble() * 0.25;
////        //double sample = fmod(phase, 0.2);
////        double sample = sin(phase) * 0.1;
////        leftChan[i] = sample;
////        rightChan[i] = sample;
////        
////        phase += dphase;
////    }
////    
////    //bufferToFill.clearActiveBufferRegion();
////}
//
//void MainComponent::releaseResources()
//{
//    // This will be called when the audio device stops, or when it is being
//    // restarted due to a setting change.
//
//    // For more details, see the help for AudioProcessor::releaseResources()
//    transportSource.releaseResources();
//}
//
////==============================================================================
//void MainComponent::paint (juce::Graphics& g)
//{
//    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
//
//    // You can add your drawing code here!
//}
//
//void MainComponent::resized()
//{
//    // This is called when the MainContentComponent is resized.
//    // If you add any child components, this is where you should
//    // update their positions.
//    double rowH = getHeight() / 5;
//    playButton.setBounds(0, 0, getWidth(), rowH);
//    stopButton.setBounds(0, rowH, getWidth(), rowH);
//    
//    volSlider.setBounds(0, rowH * 2, getWidth(), rowH);
//    
//    loadButton.setBounds(0, rowH * 3, getWidth(), rowH);
//    
//}
//
//void MainComponent::buttonClicked(juce::Button* button)
//{
//    if (button == &playButton)
//    {
//        std::cout<< "Play button was clicked " << std::endl;
//    }
//    if (button == &stopButton)
//    {
//        std::cout<< "Stop button was clicked " << std::endl;
//    }
//    if (button == &loadButton)
//    {
//        auto fileChooserFlags =
//        juce::FileBrowserComponent::canSelectFiles;
//        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
//        {
//            juce::File chosenFile = chooser.getResult();
//            loadURL(URL{chosenFile});
//        });
//        
//        
//        
////        juce::FileChooser chooser{"Select a file..."};
////        if (chooser.browseForFileToOpen())
////        {
////            loadURL(URL{chooser.getResult()});
////        }
//    }
//    
//}
//
//void MainComponent::sliderValueChanged(juce::Slider *slider)
//{
//    if (slider == &volSlider)
//    {
//        //std::cout << "vol Slider moved" << slider->getValue() << std::endl;
//        dphase = volSlider.getValue() * 0.01;
//    }
//}
//
//void MainComponent::loadURL(<#juce::URL audioURL#>)
//{
//    
//    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
//    if (reader != nullptr)
//    {
//        std::unique_ptr<juce::AudioFormatReaderSource> newSource (new juce::AudioFormatReaderSource (reader,
//                                                                                               true));
//        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
//        readerSource.reset(newSource.release());
//        transportSource.start();
//    }
//
//}


#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    setSize (800, 600);

    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        setAudioChannels (0, 2);
    }
    
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(speedSlider);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    volSlider.addListener(this);
    speedSlider.addListener(this);
    
    volSlider.setRange(0.0, 1.0);
    
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    //phase = 0.0;
   // dphase = 0.0001;
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
//    formatManager.registerBasicFormats();
//    
//    transportSource.prepareToPlay(
//                                  samplesPerBlockExpected,
//                                  sampleRate);
//    resampleSource.prepareToPlay(
//                                  samplesPerBlockExpected,
//                                  sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    //transportSource.getNextAudioBlock(bufferToFill);
    //resampleSource.getNextAudioBlock(bufferToFill);
    player1.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    //transportSource.releaseResources();
    player1.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    double rowH = getHeight() / 5;
    playButton.setBounds(0, 0, getWidth(), rowH);
    stopButton.setBounds(0, rowH, getWidth(), rowH);
    volSlider.setBounds(0, rowH * 2, getWidth(), rowH);
    speedSlider.setBounds(0, rowH * 3, getWidth(), rowH);
    loadButton.setBounds(0, rowH * 4, getWidth(), rowH);
}

void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &playButton)
    {
        std::cout<< "Play button was clicked " << std::endl;
        //transportSource.start();
        player1.start();
    }
    if (button == &stopButton)
    {
        std::cout<< "Stop button was clicked " << std::endl;
        //transportSource.stop();
        player1.stop();
    }
    if (button == &loadButton)
    {
        auto fileChooserFlags = juce::FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
        {
            juce::File chosenFile = chooser.getResult();
            if (chosenFile.existsAsFile())
            {
                //loadURL(juce::URL{chosenFile});
                player1.loadURL(juce::URL{chooser.getResult()});
            }
        });
    }
}

void MainComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volSlider)
    {
        //dphase = volSlider.getValue() * 0.01;
        player1.setGain(slider->getValue());
    }
    else if (slider == &speedSlider)
    {
        //resampleSource.setResamplingRatio(slider->getValue());
        player1.setSpeed(slider->getValue());
    }
}

//void MainComponent::loadURL(juce::URL audioURL)
//{
//    // Create an input stream directly from the URL
//    std::unique_ptr<juce::InputStream> inputStream(audioURL.createInputStream(false));
//
//    if (inputStream != nullptr)
//    {
//        auto* reader = formatManager.createReaderFor(std::move(inputStream));
//        if (reader != nullptr)
//        {
//            std::unique_ptr<juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader, true));
//            transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
//            readerSource.reset(newSource.release());
//        }
//    }
//}

