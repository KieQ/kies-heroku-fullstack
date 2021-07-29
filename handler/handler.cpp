#include "boost/date_time/posix_time/posix_time.hpp"


#include "handler.hpp"
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

#include "../db/t_flow.hpp"
#include "../utils/file.hpp"

using namespace cinatra;


namespace handler{

    void home_page(cinatra::request& req, cinatra::response& res){
        auto ip_address = req.get_header_value("X-Forwarded-For");
        SPDLOG_INFO("ip={}",ip_address);
        
        res.set_status_and_content(status_type::ok,utils::read_template("template/html/index.html"), req_content_type::html, content_encoding::gzip);
    }


    void upload_file(cinatra::request& req, cinatra::response& res){

    }

    
} // namespace handler


