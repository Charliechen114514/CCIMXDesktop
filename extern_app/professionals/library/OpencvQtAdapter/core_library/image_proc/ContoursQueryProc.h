#ifndef CONTOURSQUERYPROC_H
#define CONTOURSQUERYPROC_H
#include "CannyProcessor.h"
#include "image_proc_base.h"
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
namespace Processor {
namespace ContoursQuery {
    enum class Method {
        CHAIN_APPROX_NONE,
        CHAIN_APPROX_SIMPLE,
        CHAIN_APPROX_TC89_L1,
        CHAIN_APPROX_TC89_KCOS
    };

    static constexpr Method DEF = Method::CHAIN_APPROX_SIMPLE;

    const std::map<std::string, Method> mappings = {
        { "ALL_POINT(CHAIN_APPROX_NONE)", Method::CHAIN_APPROX_NONE },
        { "LINE(CHAIN_APPROX_SIMPLE)", Method::CHAIN_APPROX_SIMPLE },
        { "L1(CHAIN_APPROX_TC89_L1)", Method::CHAIN_APPROX_TC89_L1 },
        { "KCOS(CHAIN_APPROX_TC89_KCOS)", Method::CHAIN_APPROX_TC89_KCOS }
    };

    static const std::string DEF_STR() {
        for (const auto& it : mappings) {
            if (it.second == DEF) {
                return it.first;
            }
        }
        return "";
    }

    static const std::vector<std::string> keys() {
        std::vector<std::string> result;
        for (const auto& it : mappings) {
            result.emplace_back(it.first);
        }
        return result;
    }

    static const Method fromString(const std::string& from_name) {
        auto it = mappings.find(from_name);
        if (it == mappings.end()) {
            throw std::invalid_argument("Invalid name");
        }
        return it->second;
    }

}
}

class ContoursQueryProc : public ImageProc {
public:
    ContoursQueryProc() = default;
    ~ContoursQueryProc() override = default;
    bool process(CVImage& prev_image) override;

    inline void setCannyPackage(const std::pair<int, int>& p) {
        canny_processor.threholds_pair = p;
    }
    Processor::ContoursQuery::Method method { Processor::ContoursQuery::DEF };

private:
    CannyProcessor canny_processor;
};

#endif // CONTOURSQUERYPROC_H
