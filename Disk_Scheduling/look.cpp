#include <stdio.h>
#include <stdlib.h>

int min(int arr[], int len)
{
    int min = arr[0], index = 0;
    for (int i = 1; i < len; i++)
    {
        if (arr[i] <= min)
        {
            min = arr[i];
        }
    }

    return min;
}

int main()
{
    int noOfReq, head;
    printf("Enter no of requests: ");
    scanf("%d", &noOfReq);

    int requests[noOfReq], max_req = 0;
    printf("Enter sequence of requests:\n");
    for (int i = 0; i < noOfReq; i++)
    {
        scanf("%d", &requests[i]);
        max_req = (requests[i] >= max_req) ? requests[i] : max_req;
    }

    printf("Enter position of head: ");
    scanf("%d", &head);

    int ans = abs(max_req - head) + (max_req - min(requests, noOfReq));
    printf("Total seek time: %d\n", ans);
}
