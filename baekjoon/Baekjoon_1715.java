import java.util.PriorityQueue;
import java.util.Scanner;

public class Baekjoon_1715 {
  public static void main(String[] args){
    Scanner sc = new Scanner(System.in);
    PriorityQueue<Integer> pq = new PriorityQueue<>();
    int n = sc.nextInt();
    int result = 0;

    for (int i=0; i<n; ++i)
      pq.add(sc.nextInt());

    for (int i=0; i<n-1; ++i){
      int sum = pq.poll() + pq.poll();

      result += sum;
      pq.add(sum);
    }

    System.out.println(result);
  }
}
