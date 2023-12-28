#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int seek_time(int arr[], int head, int len)
{
    int seek_time = abs(arr[0] - head);
    for (int i = 1; i < len; i++)
        seek_time += abs(arr[i] - arr[i - 1]);

    return seek_time;
}

int main()
{
    int noOfReq, head;
    printf("Enter no of requests: ");
    scanf("%d", &noOfReq);

    int requests[noOfReq];
    printf("Enter sequence of requests:\n");
    for (int i = 0; i < noOfReq; i++)
        scanf("%d", &requests[i]);

    printf("Enter position of head: ");
    scanf("%d", &head);

    int ans = seek_time(requests, head, noOfReq);
    printf("Total seek time: %d\n", ans);
}
