public class Conditionals {
    public static void main(String[] args) {
        int age = 20;

        if (age < 18) {
            System.out.println("Minor");
        } else if (age >= 18 && age < 65) {
            System.out.println("Adult");
        } else {
            System.out.println("Senior");
        }

        // Switch (enhanced switch Java 14+)
        String status = "active";
        switch (status) {
            case "active" -> System.out.println("User is active");
            default -> System.out.println("Unknown");
        }
    }
}
