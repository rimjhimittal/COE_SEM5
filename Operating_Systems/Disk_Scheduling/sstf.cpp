#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min_index(int arr[], int len)
{
    int min = arr[0], index = 0;
    for (int i = 1; i < len; i++)
    {
        if (arr[i] <= min)
        {
            min = arr[i];
            index = i;
        }
    }

    return index;
}

int seek_time(int arr[], int head, int len)
{
    int seek_time = 0, req = len;
    while (req--)
    {
        int closest[len];
        for (int i = 0; i < len; i++)
        {
            closest[i] = abs(arr[i] - head);
        }
        seek_time += abs(head - arr[min_index(closest, len)]);
        head = arr[min_index(closest, len)];
        arr[min_index(closest, len)] = INT_MAX;
    }

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
