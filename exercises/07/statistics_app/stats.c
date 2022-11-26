#include "stdlib.h"
#include "stdio.h"
#include "signal.h"
#include "stdbool.h"
#include "stdint.h"
#include "string.h" 

static bool stat_flag = false;

struct latency_data
{
    uint32_t latency;
    uint8_t line;
    uint64_t timestamp;
};

struct stats_data
{
    uint8_t line;
    uint64_t event_count;
    double avg_latency;
    uint32_t worst_latency;
};

void sig_handler(int signal)
{
    stat_flag = true;
}

int main()
{
    struct latency_data ld = {0};
    struct stats_data sd[20] = {0};
    char *line = NULL;
    size_t len = 0;
    ssize_t lineSize = 0;
    uint8_t line_count = 0; 
    signal(SIGINT, sig_handler);

   for(;;)
    {
		//printf("Enter the line:\n");
		
		lineSize = getline(&line, &len, stdin);
		if(stat_flag)
		{
			printf("-----------------------------------------------------------------------------------------\n");
			for(int i = 0; i <= line_count; i++)
			{
				printf("IRQ line: %d Events occured : %lu Average Latency: %lf worst_latency: %d\n" , sd[i].line , sd[i].event_count , sd[i].avg_latency , sd[i].worst_latency);
			}
			printf("-----------------------------------------------------------------------------------------\n");
			stat_flag = false;
			free(line);
			return 0;
		};
		
		
		sscanf(line, "%hhd,%d,%ld" ,&ld.line, &ld.latency, &ld.timestamp);

		if(ld.line != line_count)
		{
			sd[line_count].avg_latency = sd[line_count].avg_latency/sd[line_count].event_count;
			line_count = ld.line;
		}
		
		sd[line_count].line = ld.line;
		sd[line_count].event_count += 1;
		sd[line_count].avg_latency = ld.latency;
		sd[line_count].worst_latency = (ld.latency > sd[line_count].worst_latency) ?  (ld.latency) : (sd[line_count].worst_latency);
    }
}
