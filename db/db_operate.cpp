#include "db_operate.hpp"
#include "db_manager.hpp"

namespace db
{
    void database_init()
    {
        //create t_user_info
        if(auto result = exec(R"sql(CREATE TABLE IF NOT EXISTS t_user_info (
            id              SERIAL PRIMARY KEY,
            user_name       VARCHAR(200) NOT NULL,
            password        VARCHAR(200) NOT NULL,
            create_time     INTEGER NOT NULL,
            last_login      TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        ))sql"); !result){
            SPDLOG_ERROR("Error when check if table t_user_info exists");
        }


        //check
        pqxx::work t(Database::get_conn());
        auto result = t.exec(R"sql(SELECT table_schema,table_name FROM information_schema.tables;)sql");
        for(auto it=result.begin();it!=result.end();it++){
            for(auto cit = it.begin();cit != it.end();cit++){
                SPDLOG_INFO("{}", cit.c_str());
            }
        }

    }

    bool exec(std::string_view sql)
    {
        SPDLOG_INFO("exec sql={}", sql);
        try
        {
            pqxx::work t(Database::get_conn());
            auto result = t.exec(sql);
            return result.empty();
        }
        catch (std::exception &err)
        {
            SPDLOG_ERROR("exception has occured, {}", err.what());
            return false;
        }
    }

} // namespace db
