import java.util.*;

public class DataStructures {
    public static void main(String[] args) {
        // ArrayList (dynamic array)
        List<Integer> nums = new ArrayList<>(Arrays.asList(1, 2, 3, 4, 5));
        nums.add(6);

        // HashMap (dictionary)
        Map<String, Integer> person = new HashMap<>();
        person.put("age", 28);

        // HashSet
        Set<Integer> unique = new HashSet<>(Arrays.asList(1, 2, 2, 3));

        System.out.println("List size: " + nums.size());
        System.out.println("Unique set size: " + unique.size());
    }
}
