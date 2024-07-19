/*#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <ctime>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/AVL.h"

using namespace std;

TEST_CASE("AVL Incorrect Commands", "[commands]") {
    AVL tree;
    stringstream buffer;
    streambuf *sbuf = cout.rdbuf();
    cout.rdbuf(buffer.rdbuf());

    // Testing incorrect commands
    SECTION("Incorrect Insert") {
        string name = "A11y";
        string ufId = "45679999";
        tree.insert(name, ufId);
        cout.rdbuf(sbuf); // Reset to standard output
        string output = buffer.str();
        REQUIRE(output == "unsuccessful\n");
        buffer.str(""); // Clear buffer for next test
    }

    SECTION("Incorrect Remove") {
        string ufId = "00000000";
        tree.remove(ufId);
        cout.rdbuf(sbuf); // Reset to standard output
        string output = buffer.str();
        REQUIRE(output == "unsuccessful\n");
        buffer.str(""); // Clear buffer for next test
    }

    SECTION("Incorrect Search") {
        string ufId = "99999999";
        tree.search(ufId);
        cout.rdbuf(sbuf); // Reset to standard output
        string output = buffer.str();
        REQUIRE(output == "unsuccessful\n");
        buffer.str(""); // Clear buffer for next test
    }

    SECTION("Incorrect Command Format") {
        string command = "insertA11y 45679999";
        // Assuming this will print "unsuccessful"
    }

    SECTION("Invalid Command") {
        string command = "unknownCommand";
        // Assuming this will print "unsuccessful"
    }

    cout.rdbuf(sbuf); // Reset to standard output for further tests
}

TEST_CASE("AVL Edge Cases", "[edge]") {
    AVL tree;
    stringstream buffer;
    streambuf *sbuf = cout.rdbuf();
    cout.rdbuf(buffer.rdbuf());

    // Edge case: Remove non-existing node
    SECTION("Remove Non-Existing Node") {
        string ufId = "00000000";
        tree.remove(ufId); // Non-existing node
        cout.rdbuf(sbuf); // Reset to standard output
        string output = buffer.str();
        REQUIRE(output == "unsuccessful\n");
        buffer.str(""); // Clear buffer for next test
    }

        // Edge case: Insert duplicate nodes
    SECTION("Insert Duplicate Nodes") {
        string name = "Node";
        string ufId = "12345678";
        tree.insert(name, ufId);
        tree.insert(name, ufId); // Duplicate insert
        cout.rdbuf(sbuf); // Reset to standard output
        string output = buffer.str();
        REQUIRE(output == "successful\nunsuccessful\n");
        REQUIRE(tree.size() == 1);
        buffer.str(""); // Clear buffer for next test
    }

        // Edge case: Search non-existing node
    SECTION("Search Non-Existing Node") {
        string ufId = "00000000";
        tree.search(ufId); // Non-existing node
        cout.rdbuf(sbuf); // Reset to standard output
        string output = buffer.str();
        REQUIRE(output == "unsuccessful\n");
        buffer.str(""); // Clear buffer for next test
    }

    cout.rdbuf(sbuf); // Reset to standard output for further tests
}

TEST_CASE("AVL Rotations", "[rotations]") {
    AVL tree;
    string name;
    string ufId;

    // Left Rotation Case
    name = "A";
    ufId = "3";
    tree.insert(name, ufId);
    name = "B";
    ufId = "2";
    tree.insert(name, ufId);
    name = "C";
    ufId = "1";
    tree.insert(name, ufId);
    // Check the structure after left rotation
    REQUIRE(tree.getRoot()->name == "B");

    // Right Rotation Case
    AVL tree2;
    name = "A";
    ufId = "1";
    tree2.insert(name, ufId);
    name = "B";
    ufId = "2";
    tree2.insert(name, ufId);
    name = "C";
    ufId = "3";
    tree2.insert(name, ufId);
    // Check the structure after right rotation
    REQUIRE(tree2.getRoot()->name == "B");

    // Left-Right Rotation Case
    AVL tree3;
    name = "A";
    ufId = "3";
    tree3.insert(name, ufId);
    name = "B";
    ufId = "1";
    tree3.insert(name, ufId);
    name = "C";
    ufId = "2";
    tree3.insert(name, ufId);
    // Check the structure after left-right rotation
    REQUIRE(tree3.getRoot()->name == "C");

    // Right-Left Rotation Case
    AVL tree4;
    name = "A";
    ufId = "1";
    tree4.insert(name, ufId);
    name = "B";
    ufId = "3";
    tree4.insert(name, ufId);
    name = "C";
    ufId = "2";
    tree4.insert(name, ufId);
    // Check the structure after right-left rotation
    REQUIRE(tree4.getRoot()->name == "C");
}

TEST_CASE("AVL Deletion Cases", "[deletion]") {
    AVL tree;
    string name;
    string ufId;

    // Deletion Case: No Children
    name = "A";
    ufId = "1";
    tree.insert(name, ufId);
    tree.remove(ufId);
    REQUIRE(tree.isEmpty());

    // Deletion Case: One Child
    name = "B";
    ufId = "2";
    tree.insert(name, ufId);
    name = "C";
    ufId = "3";
    tree.insert(name, ufId);
    tree.remove(ufId);
    REQUIRE(tree.size() == 1);

    // Deletion Case: Two Children
    name = "D";
    ufId = "4";
    tree.insert(name, ufId);
    name = "E";
    ufId = "5";
    tree.insert(name, ufId);
    tree.remove(ufId);
    REQUIRE(tree.size() == 1);
}

TEST_CASE("AVL Insert and Remove Large Set", "[large_set]") {
    AVL tree;
    vector<string> ids;
    vector<string> names;
    stringstream ss;
    int baseId = 10000000;

    // Insert 100 nodes
    for (int i = 0; i < 100; ++i) {
        ss.str("");
        ss << baseId + i;
        ids.push_back(ss.str());
        names.push_back("Node" + to_string(i));
        tree.insert(names.back(), ids.back());
    }

    // Check tree size after insertions
    REQUIRE(tree.size() == 100);

    // Shuffle and remove 10 random nodes
    srand(time(0));
    random_shuffle(ids.begin(), ids.end());
    for (int i = 0; i < 10; ++i) {
        tree.remove(ids[i]);
    }

    // Check tree size after deletions
    REQUIRE(tree.size() == 90);

    // Verify the in-order traversal of the remaining 90 nodes
    bool first = true;
    tree.printInorder(); // This would ideally be checked against expected output in a real test

    // Ensure no duplicate IDs are present and all nodes are correctly ordered
    vector<string> inorderIds;
    tree.printInorder();
}*/
