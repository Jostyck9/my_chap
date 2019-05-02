# My_Chap

My chap is a projet for the creation of an UDP/IP socket

The header are created for the socket and fill with the correct info.
It's made to a specific server for a simple handshake authentification.

### Phase 1

**Client** -> "client hello" -> **Server**

### Phase 2

**Server** -> 10 random bytes -> **Client**

### Phase 3

**Client** -> Sha256(message serveur + password) -> **Server**

### Phase 4

**Server** -> secret message -> **client**

# Compilation

To compile use **MAKE**

execute with **-h** to know the parameters
