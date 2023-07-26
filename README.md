# Console-Library-System

The Library System project is a console-based application that helps manage a library's books and users. It provides various functionalities for adding and managing books, users, and borrowing/returning books. The project is implemented in C++ and uses file handling to store data persistently in a text file called "Books.txt".

Key features of the Library System project include:

Add Books: The system allows the user to add books to the library. The user can input the book name, unique book ID, and the total quantity of the book available in the library.

Add Users: Users can be added to the library system. The user's name and national ID are recorded.

Search Books By Prefix: The system allows users to search for books based on a prefix of their name. It displays all book names that match the provided prefix.

Print Who Borrowed Book By Name: The system provides a functionality to print the list of users who have borrowed a specific book, based on the book's name.

Print Library By Id and Name: The system can print the entire library's book collection either by book ID or book name, in ascending order.

User Borrow Book: Users can borrow books from the library. The system checks the book's availability, and if the book is available, the user can borrow it. The book's quantity is updated accordingly.

User Return Book: Users can return books to the library. The system verifies if the user has borrowed the book and updates the book's quantity accordingly.

Print Users: The system can print the list of all users in the library, along with the books they have borrowed.

The user interacts with the system through a command-line interface, where they are presented with a menu to select the desired functionality. The project utilizes data structures like vectors to store and manage books and users efficiently.

This Library System project serves as a simple implementation of a library management system, providing basic functionalities to manage book records, user information, and book borrowing activities. It can be extended and enhanced to incorporate more advanced features, such as user authentication, more complex searching options, and fine-grained book availability tracking.
