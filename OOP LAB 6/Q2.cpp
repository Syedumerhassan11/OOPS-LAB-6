#include <iostream>
#include <vector>
#include <memory>

// Base class
class MediaFile {
protected:
    std::string filePath;
    double size;

public:
    MediaFile(const std::string& path, double sz) : filePath(path), size(sz) {}
    virtual ~MediaFile() {}

    virtual void play() const {
        std::cout << "Playing media from: " << filePath << "\n";
    }

    virtual void stop() const {
        std::cout << "Stopping media from: " << filePath << "\n";
    }
};

// Intermediate class for visual media
class VisualMedia : virtual public MediaFile {
protected:
    int resolutionX;
    int resolutionY;

public:
    VisualMedia(const std::string& path, double sz, int resX, int resY)
        : MediaFile(path, sz), resolutionX(resX), resolutionY(resY) {}

    void displayResolution() const {
        std::cout << "Resolution: " << resolutionX << "x" << resolutionY << "\n";
    }
};

// Intermediate class for audio media
class AudioMedia : virtual public MediaFile {
protected:
    int sampleRate;

public:
    AudioMedia(const std::string& path, double sz, int rate)
        : MediaFile(path, sz), sampleRate(rate) {}

    void displaySampleRate() const {
        std::cout << "Sample rate: " << sampleRate << " Hz\n";
    }
};

// Derived class for video files inheriting from both VisualMedia and AudioMedia
class VideoFile : public VisualMedia, public AudioMedia {
public:
    VideoFile(const std::string& path, double sz, int resX, int resY, int rate)
        : MediaFile(path, sz), VisualMedia(path, sz, resX, resY), AudioMedia(path, sz, rate) {}

    void play() const override {
        std::cout << "Playing video: " << filePath << " with resolution "
                  << resolutionX << "x" << resolutionY << " and sample rate " << sampleRate << " Hz\n";
    }
};

// Derived class for audio files
class AudioFile : public AudioMedia {
public:
    AudioFile(const std::string& path, double sz, int rate)
        : MediaFile(path, sz), AudioMedia(path, sz, rate) {}

    void play() const override {
        std::cout << "Playing audio: " << filePath << " with sample rate " << sampleRate << " Hz\n";
    }
};

// Derived class for image files
class ImageFile : public VisualMedia {
public:
    ImageFile(const std::string& path, double sz, int resX, int resY)
        : MediaFile(path, sz), VisualMedia(path, sz, resX, resY) {}

    void play() const override {
        std::cout << "Displaying image: " << filePath << " with resolution "
                  << resolutionX << "x" << resolutionY << "\n";
    }
};

int main() {
    std::vector<std::unique_ptr<MediaFile>> mediaFiles;

    mediaFiles.push_back(std::make_unique<VideoFile>("video.mp4", 100.0, 1920, 1080, 44100));
    mediaFiles.push_back(std::make_unique<AudioFile>("audio.mp3", 5.0, 44100));
    mediaFiles.push_back(std::make_unique<ImageFile>("image.png", 2.5, 1024, 768));

    for (const auto& media : mediaFiles) {
        media->play();
        media->stop();
    }

    return 0;
}

