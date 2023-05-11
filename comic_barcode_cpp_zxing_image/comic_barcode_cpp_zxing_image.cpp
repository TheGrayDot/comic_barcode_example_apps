#include "ReadBarcode.h"
#include "GTIN.h"

#include <iostream>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

using namespace ZXing;

std::ostream &operator<<(std::ostream &os, const Position &points) {
    for (const auto &p : points)
        os << p.x << "x" << p.y << " ";
    return os;
}

int main(int argc, char *argv[]) {
    DecodeHints hints;
    std::vector<std::string> filePaths;
    Results allResults;
    int ret = 0;

    // Hints configuration
    hints.setTextMode(TextMode::HRI);
    // hints.setEanAddOnSymbol(EanAddOnSymbol::Read);
    hints.setEanAddOnSymbol(EanAddOnSymbol::Require);
    hints.setTryDenoise(true);
    hints.setTryHarder(false);
    hints.setTryRotate(false);
    hints.setTryInvert(false);
    hints.setTryDownscale(false);
    hints.setIsPure(false);
    hints.setBinarizer(Binarizer::FixedThreshold);
    hints.setReturnErrors(true);

    if (argc != 2) {
        std::cout << "Usage: ./comic_barcode_cpp_zxing_image <image_path>" << "\n";
        return -1;
    }

    std::string filePath = argv[1];

    int width, height, channels;
    std::unique_ptr<stbi_uc, void (*)(void *)> buffer(stbi_load(filePath.c_str(), &width, &height, &channels, 3), stbi_image_free);
    if (buffer == nullptr) {
        std::cerr << "Failed to read image: " << filePath << "\n";
        return -1;
    }

    ImageView image{buffer.get(), width, height, ImageFormat::RGB};
    auto results = ReadBarcodes(image, hints);

    // if we did not find anything, insert a dummy to produce some output for each file
    if (results.empty())
        results.emplace_back();

    allResults.insert(allResults.end(), results.begin(), results.end());

    for (auto &&result : results) {
        ret |= static_cast<int>(result.error().type());

        if (result.format() == BarcodeFormat::None) {
            std::cout << "No barcode found\n";
            continue;
        }

        std::cout << "Text:       \"" << result.text() << "\"\n"
                  << "Bytes:      " << ToHex(hints.textMode() == TextMode::ECI ? result.bytesECI() : result.bytes()) << "\n"
                  << "Format:     " << ToString(result.format()) << "\n"
                  << "Identifier: " << result.symbologyIdentifier() << "\n"
                  << "Content:    " << ToString(result.contentType()) << "\n"
                  << "HasECI:     " << result.hasECI() << "\n"
                  << "Position:   " << result.position() << "\n"
                  << "Rotation:   " << result.orientation() << " deg\n"
                  << "IsMirrored: " << result.isMirrored() << "\n"
                  << "IsInverted: " << result.isInverted() << "\n"
                  << "Add-On:     " << GTIN::EanAddOn(result) << "\n";
    }
    return ret;
}
