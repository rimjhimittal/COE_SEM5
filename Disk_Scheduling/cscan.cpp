#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int min(int arr[], int len, int head)
{
    sort(arr, len);
    int val = arr[0];
    for (int i = 0; i < len; i++)
    {
        if (arr[i] <= head)
        {
            val = arr[i];
        }
        else
        {
            break;
        }
    }

    return val;
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

    int range_min = 0, range_max = max_req + (10 - 1);

    int ans = abs(range_max - head) + (range_max - range_min) + (min(requests, noOfReq, head) - range_min);
    printf("Total seek time: %d\n", ans);
}
