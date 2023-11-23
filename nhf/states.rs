// state specification in Rust

enum Tabs {
    Vax(VaxTab),
    Owners(OwnersTab),
    Animals(AnimalsTab),
}

enum VaxTab {
    Selecting(u32),
    Details(Owner, OwnerDetails),
}

enum OwnersTab {
    Searching(char*),
    Selecting(u32),
    EditingProperty(char*),
    Details(Owner, OwnerDetails),
}

enum AnimalsTab {
    Searching(char*),
    Selecting(u32),
    EditingProperty(char*),
    Details(Animal, AnimalDetails),
}

enum OwnerDetails {
    Selecting(u32),
    EditingProperty(char*),
    Details(Animal, AnimalDetails),
}

enum AnimalDetails {
    Selecting(u32),
    EditingProperty(char*),
    Details(Treatment, TreatmentDetails),
}

enum TreatmentDetails {
    Selecting(u32),
    EditingProperty(char*),
}
