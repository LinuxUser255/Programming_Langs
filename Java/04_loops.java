import java.util.Arrays;
import java.util.List;

public class Loops {
    public static void main(String[] args) {
        // For loop
        for (int i = 0; i < 5; i++) {
            System.out.print("For: " + i + " ");
        }
        System.out.println();

        // Enhanced for (range-based)
        List<Integer> numbers = Arrays.asList(10, 20, 30);
        for (int num : numbers) {
            System.out.print(num + " ");
        }
        System.out.println();

        // While
        int count = 0;
        while (count < 3) {
            System.out.println("While: " + count++);
        }
    }
}
