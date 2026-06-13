import pytest
from datetime import datetime

def pytest_html_report_title(report):
    report.title = "LMS SQE Test Report"

def pytest_configure(config):
    config._metadata = {
        "Project": "Library Management System (DSA C++)",
        "Author": "Muhammad Ahmad Khokhar & Muhammad Waqas",
        "University": "Riphah International University",
        "Test Date": datetime.now().strftime("%Y-%m-%d"),
    }