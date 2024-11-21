# Store Operation Simulation
This project was done on my first year on the Warsaw University of Technology. It executes a simulation of a small store. It was made to learn C++ and C++ OOP.

# Usage
To run this project, you need to compile all of the files (class files in corresponding directories, Structures.cpp/.hpp and main.cpp) and run main with some arguments. The usage is:
```
<executable file> <days> <starting budget> <names file path> <products file path>
```

# Classes
Below is the description of classes implemented in this project

### Class: Employee

Store employees are responsible for various tasks related to store operations, such as opening and closing the store, maintaining order, restocking, assisting customers, calculating payments, receiving payments, and issuing receipts. Different types of employees inherit from the Employee class: Cashier, Cleaner, Storekeeper, and Manager.
###### Attributes:
- first name: Randomly selected from a database of names.
- last name: Randomly selected from a database of surnames.
- work schedule: Specifies the employee's working hours for each day of the week.
- base hourly rate: Defines how much the employee earns per hour.
- hourly rate bonus: Additional pay added to the base hourly rate.
- user interface: For interacting with the simulation.
###### Methods:
- clean (Cleaner): Randomly performs cleaning tasks in the store.
- assist customer (Cashier): Handles customer purchases and calculates the total payment.
- pay employees (Manager): Processes salary payments for employees.
- speak to customers: Methods to generate dialogues employees might have with customers.
- calculate weekly salary: Computes the weekly earnings based on the work schedule and hourly rate.

### Class: Client

Clients enter and exit the store, have a specific shopping budget, and spend a defined amount of time shopping. Clients can pick products and pay for them. Clients come in various types: manager’s friend, regular customer, and tourist.
###### Attributes:
- first name: Randomly selected from a database of names.
- last name: Randomly selected from a database of surnames.
- shopping budget: The maximum amount the client can spend during a visit.
- user interface: For interacting with the simulation.
###### Methods:

    enter store
    exit store
    purchase item: Allows the client to select products within their budget.

### Class: Product

Store products are categorized, with each category associated with a specific VAT rate. Product subclasses inherit from Product: Bakery, Beverages, Dairy, Fruits and Vegetables, Cosmetics, and Industrial Goods.
###### Attributes:
- name
- price
- optional attributes: Additional attributes specific to certain product categories.
###### Methods:
- calculate price with VAT: Determines the product price including tax.
- get shelf location: Returns the shelf number where the product is located.

### Class: Receipt

Receipts provide information about the types and quantities of products sold.
###### Attributes:

    list of items: A vector of Product objects, including details about each.
    total price with tax
    total price without tax
###### Methods:
- display receipt

### Class: Store

This class stores information about products, employees, and customers in the store.
###### Attributes:
- employees: A vector of Employee objects, divided into:
    - Employees currently in the store but available.
    - Employees who are busy.
    - Employees not currently in the store but associated with it.
- clients: A vector of Client objects, divided into:
    - Clients currently in the store.
    - Potential clients who may visit.
    - products: A vector of Product objects.
    - available funds: The current balance of funds the store has.
###### Methods:
- add money to store
- withdraw money from store: For example, when the store receives new inventory and has to pay for it.
- add products
- add clients
- add employees
- update employee schedules

### Class: Random Event

Random events can occur during store operations. Each instance of this class represents a single event that may happen in the store. Events occur with specific probabilities.
###### Attributes:
- store: Uses store information needed to execute the event (e.g., available products, employees on duty).
- additional attributes: Vary depending on the specific event.
###### Methods:
- display event: Shows a description of the event in the terminal.
- execute event: Triggers specific actions involving the related objects.

### Derived Classes:
- ClientsBuysEvent
- CleanerCleansEvent
- ManagerGivesRiseEvent
- SupplierAddsProductsEvent

### Class: Event Generator

Generates random events during the simulation.
###### Attributes:
- store
- vector of event probabilities
- vector of event indices
###### Methods:
- select new products for store restocking: Used in restocking events.
- generate random events: Selects a random event and executes its corresponding method.

### Class: Simulation

The main program class that runs the store simulation.
###### Attributes:
- number of days to simulate
- store
-  probabilities vector
- file handler: Reads information about products, clients, and employees from files.
###### Methods:
- initialize first delivery
- run: Executes the entire simulation. Random events are triggered using the EventGenerator, with specific probabilities for each event.

The program loop runs for n iterations, where each iteration represents a 15-minute period of store operation. During each iteration:

- It determines whether a random event occurs.
- Executes the selected event, making necessary changes to the store and displaying information about the event.
- Checks and updates employee schedules as shifts start and end.
- At the end of the loop, the store closes, and the simulation concludes.

### Class: UserInterface

Handles displaying messages to the user.
###### Methods:
- print: Displays messages.

### Class: FileHandler

Responsible for reading file data to create objects for employees, clients, and products.
###### Attributes:
- file path

### Class: PeopleParser

Creates objects for people-related classes (Employee and Client). It uses the FileHandler class to read data (e.g., names) from files and generate the corresponding objects.
###### Attributes:
- file path