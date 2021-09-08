//
//  main.cpp
//
//  Created by Peter Sun on 1/16/21.
//

#include <iostream>
#include <vector>

class Solution {
public:
    struct JobInformation {
    public:
        int startTime;
        int endTime;
        int profit;

        JobInformation(int startTime_in, int endTime_in, int profit_in) : startTime(startTime_in), endTime(endTime_in), profit(profit_in) {}

        bool operator<(const JobInformation &jobInfo) const {
            return (endTime < jobInfo.endTime);
        }
    };

    std::vector<JobInformation> computeMaxProfit(std::vector<JobInformation> jobsWith,
                                                 std::vector<JobInformation> jobsWithout)
    {
        int profitWith = 0;
        for (auto job : jobsWith) profitWith += job.profit;
        int profitWithout = 0;
        for (auto job : jobsWithout) profitWithout += job.profit;
        return profitWith > profitWithout ? jobsWith : jobsWithout;
    }

    // Find next non-overlapping job (starting from the end)
    int findNextJob(std::vector<JobInformation> jobs, int jobStartTime, int startIndex) {
        for (int i = startIndex; i >= 0; --i) {
            if (jobs[i].endTime <= jobStartTime) return i;
        }
        return -1;
    }

    // Compute max profit including the selected job and excluding the selected job,
    // iterating in decreasing end time
    std::vector<JobInformation> computeMostProfitableSchedule(std::vector<JobInformation> jobs, int currIndex) {
        if (currIndex < 0) return std::vector<JobInformation>();

        std::vector<JobInformation> scheduleWithCurrIndex(1, JobInformation(jobs[currIndex].startTime, jobs[currIndex].endTime, jobs[currIndex].profit));

        // Compute max profit with the currIndex
        int nextNonOverlappingJob = findNextJob(jobs, scheduleWithCurrIndex.back().startTime, currIndex - 1);
        if (nextNonOverlappingJob != -1) {
            auto nextNonOverlappingSchedule = computeMostProfitableSchedule(jobs, nextNonOverlappingJob);
            scheduleWithCurrIndex.insert(scheduleWithCurrIndex.end(), nextNonOverlappingSchedule.begin(), nextNonOverlappingSchedule.end());
        }

        // Compute max profit without the currIndex
        std::vector<JobInformation> scheduleWithoutCurrIndex;
        auto nextWithoutCurrIndex = computeMostProfitableSchedule(jobs, currIndex - 1);
        scheduleWithoutCurrIndex.insert(scheduleWithoutCurrIndex.end(), nextWithoutCurrIndex.begin(), nextWithoutCurrIndex.end());

        // Determine highest max profit from two above
        return computeMaxProfit(scheduleWithCurrIndex, scheduleWithoutCurrIndex);
    }

    int jobScheduling(std::vector<int> &startTime, std::vector<int> &endTime, std::vector<int> &profit) {
        // First sort all jobs by earliest end time
        std::vector<JobInformation> sortedJobs;
        for (int i = 0; i < startTime.size(); ++i) {
            sortedJobs.push_back(JobInformation(startTime[i], endTime[i], profit[i]));
        }
        std::sort(sortedJobs.begin(), sortedJobs.end());
        auto maxSchedule = computeMostProfitableSchedule(sortedJobs, sortedJobs.size() - 1);
        std::reverse(maxSchedule.begin(), maxSchedule.end());
        std::cout << "Max Schedule is: \n";
        int totalProfit = 0;
        for (auto job : maxSchedule) {
            std::cout << "Time: [" << job.startTime << "-" << job.endTime << "]\n";
            std::cout << "Profit: $" << job.profit << "\n";
            totalProfit += job.profit;
        }
        std::cout << "TOTAL PROFIT: $" << totalProfit << "\n";
        return totalProfit;
    }
};

int main(int argc, const char *argv[]) {
    Solution solution;
    std::cout << "Welcome to the Job Scheduler!\n";
    std::cout << "Please type the times and profits in this format:\n";
    std::cout << "startTime = [1,2,3...], endTime = [2,3,4...], profit = [10,20,30...]\n";
    std::cout << "Input: ";
    std::string tmp;
    std::string startTimesStr;
    std::string endTimesStr;
    std::string profitsStr;
    std::vector<int> startTimes;
    std::vector<int> endTimes;
    std::vector<int> profits;
    std::cin >> tmp >> tmp >> startTimesStr >> tmp >> tmp >> endTimesStr >> tmp >> tmp >> profitsStr;
    startTimesStr.pop_back();
    endTimesStr.pop_back();
    std::string startTime = "";
    std::string endTime = "";
    std::string profit = "";
    for (auto startTimeChar : startTimesStr) {
        if (startTimeChar == '[') continue;
        if (startTimeChar == ']') {
            startTimes.push_back(std::stoi(startTime));
            continue;
        }
        if (startTimeChar == ',' && startTime.size() > 0) {
            startTimes.push_back(std::stoi(startTime));
            startTime = "";
            continue;
        }
        startTime += startTimeChar;
    }
    for (auto endTimeChar : endTimesStr) {
        if (endTimeChar == '[') continue;
        if (endTimeChar == ']') {
            endTimes.push_back(std::stoi(endTime));
            continue;
        }
        if (endTimeChar == ',' && endTime.size() > 0) {
            endTimes.push_back(std::stoi(endTime));
            endTime = "";
            continue;
        }
        endTime += endTimeChar;
    }
    for (auto profitChar : profitsStr) {
        if (profitChar == '[') continue;
        if (profitChar == ']') {
            profits.push_back(std::stoi(profit));
            continue;
        }
        if (profitChar == ',' && profit.size() > 0) {
            profits.push_back(std::stoi(profit));
            profit = "";
            continue;
        }
        profit += profitChar;
    }

    solution.jobScheduling(startTimes, endTimes, profits);
    return 0;
}
