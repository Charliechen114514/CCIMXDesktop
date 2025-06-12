#ifndef CONTOURSQUERYPROC_H
#define CONTOURSQUERYPROC_H

#include "CannyProcessor.h"
#include "image_proc_base.h"
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

/**
 * @brief The Processor namespace contains different image processing categories.
 */
namespace Processor {

/**
 * @brief The ContoursQuery namespace provides enumeration and mapping utilities for contour detection methods.
 */
namespace ContoursQuery {

    /**
     * @brief Enumeration of different contour approximation methods.
     *
     * These correspond to OpenCV's chain approximation flags used in contour detection.
     */
    enum class Method {
        CHAIN_APPROX_NONE,     ///< All points are stored.
        CHAIN_APPROX_SIMPLE,   ///< Compresses horizontal, vertical, and diagonal segments.
        CHAIN_APPROX_TC89_L1,  ///< Teh-Chin approximation algorithm (L1).
        CHAIN_APPROX_TC89_KCOS ///< Teh-Chin approximation algorithm (K-cosine).
    };

    /**
     * @brief The default contour approximation method.
     */
    static constexpr Method DEF = Method::CHAIN_APPROX_SIMPLE;

    /**
     * @brief String-to-enum mapping for contour approximation methods.
     */
    const std::map<std::string, Method> mappings = {
        { "ALL_POINT(CHAIN_APPROX_NONE)", Method::CHAIN_APPROX_NONE },
        { "LINE(CHAIN_APPROX_SIMPLE)", Method::CHAIN_APPROX_SIMPLE },
        { "L1(CHAIN_APPROX_TC89_L1)", Method::CHAIN_APPROX_TC89_L1 },
        { "KCOS(CHAIN_APPROX_TC89_KCOS)", Method::CHAIN_APPROX_TC89_KCOS }
    };

    /**
     * @brief Gets the default method's string representation.
     * @return A string describing the default method.
     */
    static const std::string DEF_STR() {
        for (const auto& it : mappings) {
            if (it.second == DEF) {
                return it.first;
            }
        }
        return "";
    }

    /**
     * @brief Returns a list of all method keys (descriptive names).
     * @return A vector of method description strings.
     */
    static const std::vector<std::string> keys() {
        std::vector<std::string> result;
        for (const auto& it : mappings) {
            result.emplace_back(it.first);
        }
        return result;
    }

    /**
     * @brief Converts a string to a contour method enumeration.
     * @param from_name The string representation of the method.
     * @return The corresponding Method enum.
     * @throws std::invalid_argument if the string is not found.
     */
    static const Method fromString(const std::string& from_name) {
        auto it = mappings.find(from_name);
        if (it == mappings.end()) {
            throw std::invalid_argument("Invalid name");
        }
        return it->second;
    }

} // namespace ContoursQuery

} // namespace Processor

/**
 * @brief The ContoursQueryProc class performs edge detection followed by contour detection.
 *
 * This processor uses Canny edge detection as a pre-processing step and then finds contours
 * using the specified contour approximation method.
 */
class ContoursQueryProc : public ImageProc {
public:
    /**
     * @brief Constructs a ContoursQueryProc with default method and Canny processor.
     */
    ContoursQueryProc() = default;

    /**
     * @brief Destructor.
     */
    ~ContoursQueryProc() override = default;

    /**
     * @brief Processes the image using Canny edge detection followed by contour detection.
     * @param prev_image The input/output image.
     * @return true if processing succeeds.
     */
    bool process(CVImage& prev_image) override;

    /**
     * @brief Sets the Canny threshold pair used in edge detection.
     * @param p The pair of lower and upper thresholds.
     */
    inline void setCannyPackage(const std::pair<int, int>& p) {
        canny_processor.threholds_pair = p;
    }

    /**
     * @brief The contour approximation method used for this processor.
     */
    Processor::ContoursQuery::Method method { Processor::ContoursQuery::DEF };

private:
    /**
     * @brief Internal Canny processor used for edge detection.
     */
    CannyProcessor canny_processor;
};

#endif // CONTOURSQUERYPROC_H
