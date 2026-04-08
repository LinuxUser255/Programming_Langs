class Person {
    String name;
    int age;

    Person(String name, int age) {
        this.name = name;
        this.age = age;
    }

    void introduce() {
        System.out.println("Hi, I'm " + name + " and I'm " + age + " years old.");
    }
}

public class OopBasics {
    public static void main(String[] args) {
        Person p = new Person("Emma", 27);
        p.introduce();
    }
}
