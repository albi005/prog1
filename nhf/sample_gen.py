import time
import random

names = ["Bodri", "Cirmi", "Zsemle", "Berci", "Dundi", "Csokis", "Mogyi", "Bogyó", "Szofi", "Répa"]

descriptions = ["Fogtisztítás", "Általános ellenőrzés", "Vakcina frissítés", "Rutin oltás", "Sérülés kezelése",
                "Szemvizsgálat", "Fül vizsgálat", "Vakcina beadás", "Egészségügyi tanácsadás", "Vírusellenes kezelés"]

current_time = int(time.time())
two_years_ago = int(time.time() - (2 * 365 * 24 * 60 * 60))

# Function to generate random date between three years ago and the current time
def generate_random_date():
    return random.randint(two_years_ago, current_time)

# Function to generate 'treatments' data with names, descriptions, and random dates
def generate_treatments_data():
    treatments_data = ""
    for i in range(1, 60):
        treatments_data += f"{i}\n"
        treatments_data += f"{random.randint(1, 20)}\n"  # Animal ID (example pattern)
        treatments_data += f"{generate_random_date()}\n"  # Random Date
        treatments_data += f"{random.randint(0, 1)}\n"  # Rabies vaccine
        treatments_data += f"{random.choice(descriptions)}\n"  # Treatment description

    return treatments_data

if __name__ == "__main__":
    generated_data = generate_treatments_data()
    print(generated_data)

