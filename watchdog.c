#include "watchdog.h"

void* watchdog_thread(void* thread_data)
{
    Thread_data* t_data = (Thread_data*)thread_data;

    while((t_data->flag_watchdog != exec_stop)&& (!done))
    {
        t_data->flag_watchdog = reset_flag;
        sleep(2);

        if(t_data->flag_watchdog != exec_all)
        {
            unsigned int temp_flag_watchdog = t_data->flag_watchdog;
            t_data->flag_watchdog = exec_stop;

            if((temp_flag_watchdog | exec_reader) != temp_flag_watchdog)
            {
                char* info_reader = "thread - reader wasn't executed during last two second\n";
                printf("%s", info_reader);
                fprintf(logger_file,"%s", info_reader);
            }
            if((temp_flag_watchdog | exec_analyzer) != temp_flag_watchdog)
            {
                char* info_analyzer = "thread - analyzer wasn't executed during last two second\n";
                printf("%s", info_analyzer);
                fprintf(logger_file,"%s", info_analyzer);
            }
            if((temp_flag_watchdog | exec_printer) != temp_flag_watchdog)
            {
                char* info_printer = "thread - printer wasn't executed during last two second\n";
                printf("%s", info_printer);
                fprintf(logger_file,"%s", info_printer);
            }
            if((temp_flag_watchdog | exec_logger) != temp_flag_watchdog)
            {
                char* info_logger = "thread - logger wasn't executed during last two second\n";
                printf("%s", info_logger);
                fprintf(logger_file,"%s", info_logger);
            }
        }
    }

    return thread_data;
}
