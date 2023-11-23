// Forward declaration of structs
typedef struct Owner Owner;
typedef struct Animal Animal;

// Definition of the Animals structure
typedef struct {
    // Define the properties of Animals here
    // For example:
    char name[50];
    int age;
} Animals;

// Struct definitions
struct Owner {
    Animal* animals; // Changed to Animal* instead of Animals*
};

struct Animal {
    Owner* owner;
};

int main() {
    // Your code logic can go here
    return 0;
}

