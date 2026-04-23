

#include <iostream>
#include <string>
#include <cstring>
#include "MemoryRiver.hpp"

using namespace std;

struct TestStruct {
    int id;
    char name[20];
    double score;
    
    TestStruct() : id(0), score(0.0) {
        name[0] = '\0';
    }
    
    TestStruct(int i, const string& n, double s) : id(i), score(s) {
        strncpy(name, n.c_str(), 19);
        name[19] = '\0';
    }
};

int main() {
    // Test MemoryRiver with TestStruct
    MemoryRiver<TestStruct, 2> mr("test.dat");
    
    // Initialize the file
    mr.initialise();
    
    // Test writing and reading
    TestStruct t1(1, "Alice", 95.5);
    TestStruct t2(2, "Bob", 87.0);
    TestStruct t3(3, "Charlie", 92.3);
    
    // Write objects
    int index1 = mr.write(t1);
    int index2 = mr.write(t2);
    int index3 = mr.write(t3);
    
    cout << "Written objects at indices: " << index1 << ", " << index2 << ", " << index3 << endl;
    
    // Read objects
    TestStruct read1, read2, read3;
    mr.read(read1, index1);
    mr.read(read2, index2);
    mr.read(read3, index3);
    
    cout << "Read objects:" << endl;
    cout << "ID: " << read1.id << ", Name: " << read1.name << ", Score: " << read1.score << endl;
    cout << "ID: " << read2.id << ", Name: " << read2.name << ", Score: " << read2.score << endl;
    cout << "ID: " << read3.id << ", Name: " << read3.name << ", Score: " << read3.score << endl;
    
    // Test update
    TestStruct updated(2, "Bob Updated", 90.0);
    mr.update(updated, index2);
    
    TestStruct read_updated;
    mr.read(read_updated, index2);
    cout << "After update - ID: " << read_updated.id << ", Name: " << read_updated.name << ", Score: " << read_updated.score << endl;
    
    // Test delete and space reuse
    mr.Delete(index1);
    cout << "Deleted object at index " << index1 << endl;
    
    // Write a new object - should reuse the deleted space
    TestStruct t4(4, "David", 88.5);
    int index4 = mr.write(t4);
    cout << "New object written at index: " << index4 << " (should be same as deleted index: " << index1 << ")" << endl;
    
    // Test info functions
    int info1, info2;
    mr.get_info(info1, 1);
    mr.get_info(info2, 2);
    cout << "Info values: " << info1 << ", " << info2 << endl;
    
    mr.write_info(42, 2);
    mr.get_info(info2, 2);
    cout << "After writing 42 to info2: " << info2 << endl;
    
    cout << "All tests completed successfully!" << endl;
    
    return 0;
}
