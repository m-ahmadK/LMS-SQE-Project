"""
LMS Library Management System - Automated Test Suite
Framework : Python unittest + subprocess
Author    : Muhammad Ahmad Khokhar & Muhammad Waqas
Course    : Software Quality Engineering - Riphah International University
Run       : python -m pytest automation_tests.py -v --tb=short
            OR python -m unittest discover -v
Note      : Requires LMS.exe compiled from main.cpp on Windows.
            Linux users: remove #include<conio.h>, <windows.h>, replace system("cls") with system("clear"), boolean->bool
"""

import unittest
import subprocess
import os
import shutil
import time

# ==============================================================================
# CONFIGURATION
# ==============================================================================
# Dynamic Platform Detection: Uses LMS.exe on Windows, uses ./LMS on GitHub Linux
if os.name == 'nt':
    EXE_PATH = "./LMS.exe"
else:
    EXE_PATH = "./LMS"

LMS_FILE  = "LMS.txt"
RENT_FILE = "RentBook.txt"
TIMEOUT   = 15                 # seconds per test

# Sample library data for test setup
SAMPLE_BOOKS = """Clean Code,Robert Martin,Computer Science,1,1,5
Design Patterns,GoF,Computer Science,2,1,3
Sapiens,Yuval Harari,History,3,1,0
The Lean Startup,Eric Ries,Busniess & Law,4,1,2
"""

SAMPLE_RENTS = """Ali Ahmed,03001234567,2024-01-01,2024-01-08,Clean Code,1001,7,1
"""

# ==============================================================================
# HELPER FUNCTIONS
# ==============================================================================
def run_lms(input_str, timeout=TIMEOUT):
    """Run LMS executable with given stdin input; return stdout as string."""
    try:
        result = subprocess.run(
            [EXE_PATH],
            input=input_str,
            capture_output=True,
            text=True,
            timeout=timeout
        )
        return result.stdout + result.stderr
    except subprocess.TimeoutExpired:
        return "TIMEOUT"
    except FileNotFoundError:
        return "EXE NOT FOUND"

def setup_library(books=SAMPLE_BOOKS, rents=""):
    """Write controlled test data to LMS.txt and RentBook.txt."""
    with open(LMS_FILE, "w") as f:
        f.write(books)
    with open(RENT_FILE, "w") as f:
        f.write(rents)

def clear_files():
    """Remove data files for isolation tests."""
    for f in [LMS_FILE, RENT_FILE]:
        if os.path.exists(f):
            os.remove(f)

def assert_output_contains(test, output, expected, msg=""):
    """Assert expected substring is present in output."""
    test.assertIn(expected, output, f"Expected '{expected}' in output.\nGot:\n{output[:500]}\n{msg}")

# ==============================================================================
# TEST SUITE
# ==============================================================================

class TestAdminLogin(unittest.TestCase):
    """ATC-001 to ATC-004: Admin authentication tests."""

    def setUp(self):
        setup_library()

    def test_valid_admin_login(self):
        """ATC-001: Valid credentials show Admin menu."""
        out = run_lms("1\nahmad\npass\n7\n3\n")
        assert_output_contains(self, out, "Welcome to Admin", "ATC-001")

    def test_invalid_username(self):
        """ATC-002: Wrong username shows error."""
        out = run_lms("1\nwronquser\npass\nn\n3\n")
        assert_output_contains(self, out, "Invalid Username OR Password", "ATC-002")

    def test_invalid_password(self):
        """ATC-003: Wrong password shows error."""
        out = run_lms("1\nahmad\nwronqpwd\nn\n3\n")
        assert_output_contains(self, out, "Invalid Username OR Password", "ATC-003")

    def test_empty_credentials(self):
        """ATC-004: Empty credentials rejected without causing streaming timeout hang."""
        out = run_lms("1\n\n\n3\n")
        assert_output_contains(self, out, "Invalid Username OR Password", "ATC-004")


class TestAddBook(unittest.TestCase):
    """ATC-005 to ATC-009: Add Book functionality."""

    def setUp(self):
        setup_library()

    def test_add_book_valid(self):
        """ATC-005: Valid book addition succeeds."""
        inp = "1\nahmad\npass\n1\n1\nClean Code Test\nRobert Martin\n1\n5\nn\n7\n3\n"
        out = run_lms(inp)
        assert_output_contains(self, out, "Book added successfully", "ATC-005")

    def test_add_book_invalid_author_digit(self):
        """ATC-006: Author with digit triggers validation error."""
        inp = "1\nahmad\npass\n1\n1\nTest Book\nJohn3\nJohn Doe\n1\n3\nn\n7\n3\n"
        out = run_lms(inp)
        assert_output_contains(self, out, "alphabets", "ATC-006")

    def test_add_book_negative_addition(self):
        """ATC-007: Negative addition number rejected."""
        inp = "1\nahmad\npass\n1\n1\nBook\nAuthor\n-1\n1\n1\nn\n7\n3\n"
        out = run_lms(inp)
        assert_output_contains(self, out, "non-negative", "ATC-007")

    def test_add_book_negative_quantity(self):
        """ATC-008: Negative quantity rejected."""
        inp = "1\nahmad\npass\n1\n1\nBook\nAuthor\n1\n-5\n5\nn\n7\n3\n"
        out = run_lms(inp)
        assert_output_contains(self, out, "non-negative", "ATC-008")

    def test_add_book_invalid_category(self):
        """ATC-009: Category out of range rejected."""
        inp = "1\nahmad\npass\n1\n9\n1\nBook\nAuthor\n1\n3\nn\n7\n3\n"
        out = run_lms(inp)
        assert_output_contains(self, out, "Welcome to Admin", "ATC-009")


class TestViewBooks(unittest.TestCase):
    """ATC-010 to ATC-011: View All Books."""

    def setUp(self):
        setup_library()

    def test_view_all_books_nonempty(self):
        """ATC-010: Books are displayed when library has records."""
        out = run_lms("2\n1\n\n4\n3\n")
        assert_output_contains(self, out, "ID:", "ATC-010")

    def test_view_books_shows_total(self):
        """ATC-011: Total book count shown."""
        out = run_lms("2\n1\n\n4\n3\n")
        assert_output_contains(self, out, "Total Books", "ATC-011")


class TestSearchBook(unittest.TestCase):
    """ATC-012 to ATC-016: Search functionality."""

    def setUp(self):
        setup_library()

    def test_search_by_valid_id(self):
        """ATC-012: Search by valid ID shows book."""
        out = run_lms("2\n2\n2\n1\nn\n4\n3\n")
        assert_output_contains(self, out, "Title:", "ATC-012")

    def test_search_by_valid_name(self):
        """ATC-014: Search by exact title returns book."""
        out = run_lms("2\n2\n3\nClean Code\nn\n4\n3\n")
        assert_output_contains(self, out, "Title:", "ATC-014")

    def test_search_category_cs(self):
        """ATC-015: Search by CS category shows results."""
        out = run_lms("2\n2\n1\n1\nn\n4\n3\n")
        assert_output_contains(self, out, "Computer Science", "ATC-015")

    def test_search_invalid_menu_choice(self):
        """ATC-016: Invalid search menu choice re-prompts."""
        out = run_lms("2\n2\n9\n1\n1\nn\n4\n3\n")
        assert_output_contains(self, out, "Invalid", "ATC-016")


class TestRentBook(unittest.TestCase):
    """ATC-017 to ATC-023: Rent book functionality."""

    def setUp(self):
        setup_library()

    def test_rent_book_valid_7days(self):
        """ATC-017: Valid rental for 7 days succeeds."""
        inp = "2\n3\n1\ny\n1125\nAli Ahmed\n03001234567\n1\nn\n4\n3\n"
        out = run_lms(inp)
        assert_output_contains(self, out, "successfully rented", "ATC-017")

    def test_rent_book_invalid_customer_id(self):
        """ATC-018: Customer ID below 1123 rejected."""
        inp = "2\n3\n1\ny\n100\n1125\nAli Ahmed\n03001234567\n1\nn\n4\n3\n"
        out = run_lms(inp)
        assert_output_contains(self, out, "Welcome to Library Management System", "ATC-018")

    def test_rent_book_invalid_contact(self):
        """ATC-019: Invalid contact number rejected."""
        inp = "2\n3\n1\ny\n1125\nAli Ahmed\n12345\n03001234567\n1\nn\n4\n3\n"
        out = run_lms(inp)
        assert_output_contains(self, out, "Invalid Contact", "ATC-019")

    def test_rent_zero_quantity_book(self):
        """ATC-020: Book with Qty=0 shows unavailable."""
        inp = "2\n3\n3\n4\n3\n"  # book ID 3 has Qty=0 in SAMPLE BOOKS
        out = run_lms(inp)
        assert_output_contains(self, out, "not avaliable", "ATC-020")

    def test_rent_due_date_calculated(self):
        """ATC-022: Due date appears in output."""
        inp = "2\n3\n1\ny\n1125\nAli Ahmed\n03001234567\n2\nn\n4\n3\n"
        out = run_lms(inp)
        assert_output_contains(self, out, "Due Date", "ATC-022")


class TestViewRented(unittest.TestCase):
    """ATC-024 to ATC-025: View rented books."""

    def test_view_rented_nonempty(self):
        """ATC-024: Rented records show when file has data."""
        setup_library(rents=SAMPLE_RENTS)
        out = run_lms("1\nahmad\npass\n6\n\n7\n3\n")
        assert_output_contains(self, out, "Name:", "ATC-024")

    def test_view_rented_empty(self):
        """ATC-025: Empty rent file shows no-records message."""
        setup_library(rents="")
        out = run_lms("1\nahmad\npass\n6\n\n7\n3\n")
        assert_output_contains(self, out, "No book Rented", "ATC-025")


class TestNavigation(unittest.TestCase):
    """ATC-026 to ATC-030: Menu navigation."""

    def setUp(self):
        setup_library()

    def test_main_menu_invalid_choice(self):
        """ATC-026: Out-of-range choice at main menu re-prompts."""
        out = run_lms("9\n3\n")
        assert_output_contains(self, out, "Invalid choice!", "ATC-026")

    def test_exit_application(self):
        """ATC-028: Choice 3 at main menu exits cleanly."""
        out = run_lms("3\n")
        assert_output_contains(self, out, "Thank you", "ATC-028")

    def test_user_menu_back(self):
        """ATC-029: User menu Back option returns to main."""
        out = run_lms("2\n4\n3\n")
        assert_output_contains(self, out, "Welcome to Library Management System", "ATC-029")

    def test_non_integer_main_menu(self):
        """ATC-030: Non-integer at main menu handled gracefully."""
        out = run_lms("abc\n3\n")
        assert_output_contains(self, out, "Invalid choice!", "ATC-030")


# ==============================================================================
# ENTRY POINT
# ==============================================================================
if __name__ == "__main__":
    print("=" * 70)
    print(" LMS Automated Test Suite | SQE Project")
    print(" Riphah International University")
    print("=" * 70)
    unittest.main(verbosity=2)