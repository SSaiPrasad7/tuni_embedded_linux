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
struct overall_stats_data
{
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
    struct overall_stats_data total = {0};
    char *line = NULL;
    size_t len = 0;
    ssize_t lineSize = 0;
    signal(SIGINT, sig_handler);

   for(;;)
    {
		lineSize = getline(&line, &len, stdin);
		if(stat_flag)
		{
			printf("-----------------------------------------------------------------------------------------\n");
			for(int i = 0; i < 16; i++)
			{
				sd[i].avg_latency = (sd[i].avg_latency)/(sd[i].event_count);
				printf("IRQ line: %u Events occured : %lu Average Latency: %lf worst_latency: %u\n" , sd[i].line , sd[i].event_count , sd[i].avg_latency , sd[i].worst_latency);
				
				total.event_count += sd[i].event_count;
				total.avg_latency += sd[i].avg_latency;
				total.worst_latency = (sd[i].worst_latency > total.worst_latency) ?  (sd[i].worst_latency ) : (total.worst_latency);	
			}
			total.avg_latency = total.avg_latency /total.event_count;
			printf("Overall Events occured : %lu Average Latency: %lf worst_latency: %u\n" , total.event_count , total.avg_latency , total.worst_latency);
			printf("-----------------------------------------------------------------------------------------\n");
			stat_flag = false;
			free(line);
			return 0;
		}
		if(lineSize !=-1)
		{
			sscanf(line, "%hhd,%d,%ld" ,&ld.line, &ld.latency, &ld.timestamp);
			sd[ld.line].line = ld.line;
			sd[ld.line].event_count += 1;
			sd[ld.line].avg_latency += ld.latency;
			sd[ld.line].worst_latency = (ld.latency > sd[ld.line].worst_latency) ?  (ld.latency) : (sd[ld.line].worst_latency);
		}
    }
}
