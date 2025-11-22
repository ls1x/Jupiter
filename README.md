![jupiter](images/jupiter.png)

### Description
**Jupiter** is a tool designed for exploit developers, reverse engineers, and offensive security students who want to automate the creation of payloads for **stack-based buffer overflow** vulnerabilities.

It allows you to input hexadecimal values (addresses, offsets, raw bytes, etc.), safely validate them, and assemble a fully structured payload. The final result can be exported directly to a file.

---

### Features

-  Hex input with validation and error handling  
-  Semi-automatic payload construction  
-  Payload export to file  
-  Modular architecture (`Hex` and `Payload` classes)  
-  Hex normalization utilities  
-  Focused on Stack-Based BOF workflows  
-  Clean, extensible C++ codebase

---

### Installation

Clone the repository:

```bash
git clone https://github.com/ls1x/Jupiter.git
cd Jupiter
```

Compile manually:

```bash
make
```

---

### Usage

Run the tool:

```bash
./bin/Jupiter.bin
```

---

### Example flow:

When the program starts, the user is presented with the interactive prompt:

```
Jupiter❯
```

Available commands:

```
[C] offset    - Adds a string offset.
[C] string    - Appends a custom string to the payload.
[C] load      - Loads an address (hex).
[C] add       - Adds two addresses or offsets.
[C] show      - Displays stored addresses.
[C] delete    - Removes a stored address.
[C] generate  - Inserts loaded addresses into the payload.
[C] clean     - Clears the current payload.
[C] print     - Prints the payload to stdout.
[C] output    - Saves the payload to a file.
[C] cancel    - Cancels the current command.
[C] exit      - Exits the application.
[C] help      - Shows the help menu.
```

#### Typical Workflow

1. **Set the initial offset** based on the vulnerable application's buffer size:
   ```
   Jupiter❯ offset 130
   ```
   Offsets are incremental, so smaller offsets can be added later if needed.

2. **Load the desired return address** in hexadecimal:
   ```
   Jupiter❯ load ff12ff34
   ```

3. **Generate the payload** by inserting the normalized address:
   ```
   Jupiter❯ generate
   ```

4. **Append custom data** after the address if necessary:
   ```
   Jupiter❯ string ABCD
   ```

5. **Preview the final payload**:
   ```
   Jupiter❯ print
   ```

6. **Clean the payload** and rebuild if something is incorrect:
   ```
   Jupiter❯ clean
   ```

7. **Export the payload** to a file:
   ```
   Jupiter❯ output exploit.bin

---

### Credits

Created by **Lucas Amorim**, passionate about exploit development, reverse engineering, and low-level programming.
