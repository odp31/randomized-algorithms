public class QuickSelect
  {
    public static int randomizedQuickSelect(int[] arr, int left, int right, int k)
    {
      if(left == right)
      {
        return arr[left];
      }
      int pivotIndex = partitionRandomized(arr, left, right);
      int pivotDistance = pivotIndex - left + 1;
      if(k == pivotDistance)
      {
        return arr[pivotIndex];
      }
      else if(k < pivotDistance)
      {
        return randomizedQuickSelect(arr, left, pivotIndex - 1, k);
      }
      else
      {
        return randomizedQuickSelect(arr, pivotIndex + 1, right, k - pivotDistance)
      }
    }
    private static int partitionRandomized(int[] arr, int left, int right)
    {
      int randomIndex = left + (int) (Math.random() * (right - left + 1));
      swap(arr, randomIndex, right);
      return partition(arr, left, right);
    }
    private static int partition(int[] arr, int left, int right)
    {
      int pivot = arr[right];
      int i = left - 1;
      for(int j = left; j < right; j++)
        {
          if(arr[j] <= pivot)
          {
            i++;
            swap(arr, i, j);
          }
        }
      swap(arr, i+1, right);
      return i+1;
    }
    private static void swap(int[] arr, int i, int j)
    {
      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
    public static void main(String[] args)
    {
      int[] arr = {7, 10, 4, 3, 20, 15};
      int k = 3; 
      int kthSmallest = randomizedQuickSelect(arr, 0, arr.length - 1, k);
      System.out.println("The " + k + "th smallest element is: " + kthSmallest);
    }
  }
      
      
