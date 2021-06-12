# Priority-Queue-and-Hashing
 It is a data structures assignment consisting of two parts in the given scenario.
 
 ## Problem
Let say user A and user B try to access File X from their computer systems.
• If both A and B wants to read the File X, then there is no problem
• If both A and B wants to update(write) the File X. This can create a problem, and system will be confused which value to retain.
• If A wants to write on the File X and B wants to read the File X. This is also problematic. As A is updating file X and B tries to read X, the user B can read some invalid values.
The most easy and simple solution is that we allow the different users to simultaneously read a file, but we do not allow them to simultaneously update a file. That is, if one user wants to write\update an existing file then other users must wait till he is done.

## How to run?
1. Download/ Clone the project
2. Run the cpp file in your preferred IDE for C++.
3. Follow the options given on the menu

![Capture](https://user-images.githubusercontent.com/68819501/121785178-b4642f00-cbd1-11eb-827a-f7e2c20bf55e.PNG)

## Part 1: a template-based Priority Queue implemented as Max heap using dynamic array or STL vectors.
### Functionalities
• BuildQueue: Takes in an unsorted array and convert in to a priority queue
• ExtractMax: Remove and return the maximum element
• FindMax: Return the maximum value in O(1) time
• FindMin: Return the minimum value in O(1) time
• Insert: Insert a value with given priority
• size
• empty
## Part 2: Build a generic template-based Hash Table to maintain a repository of the files. The hash table will use chaining to resolve collision.
Each node in the linked list will have a pointer to a priority queue of the users who wants to access the file, we will call it waiting queue. If a user requests an access to a file. We will check the file’s waiting priority queue. If queue is empty the user will be granted access otherwise, he will be inserted in the particular file’s waiting queue with given priority.
### Functionalities
• Insert a file in the hash table using a hash function based on file id
#### • Request File Access
  o Get User Id and File Id as input
  o Get priority as input
▪ user can either give a number for priority or
▪ specify priority is high or low
• If priority is high, then you will assign the user a number(priority) that is maximum in the given file’s waiting queue. (use FindMax function in the priority queue)
• If priority is low, then you will assign the user a number(priority) that is minimum value in the
given file’s current waiting queue. (use FindMin function in the priority queue)
  o Insert a user with given id in the file’s waiting queue with given priority. If waiting queue is empty and no user is
  currently accessing the file, give the user immediate access to the file.
  o If file does not exist print error message
#### • Release File
   o If a user no longer needs to access a file, provide access to the next user with highest priority.
▪ If the next highest priority user in waiting queue wants a write access, then he got exclusive access to the file.
▪ However, if the next user with highest priority wants a read access then we grant access to all the top priority users in the queue that want read access till we find a user with write access.
#### • Print the Hash table:
   o Print the list of the files in Hash table along with the user’s ids who are currently accessing the file and the next user to get the access.
#### • Load the data regarding files and users from the given input file
  o Input File Format
  1. File Id is a number between 5000-99999
  2. User Id is an integer in a range 0-10000
  3. Priority is an integer in a range 0-100
  4. File Access is a character R or W
#### • Provide a menu with following options:
  o Print Hash table with file information
  o Load data
  o Insert a file
  o Delete a file
      ▪ Delete the file only if no one is currently accessing it
  o Request an access to a file by a user
      ▪ Get user id, file id and access type (read or write) and perform the desire operation
  o Release the file by a user
      ▪ Get user id and file id and perform the desire operation
