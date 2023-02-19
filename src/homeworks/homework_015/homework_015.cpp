#include <iostream>
#include <string>
using namespace std;

enum HTTPError
{
    ERROR_400 = 400,
    ERROR_401 = 401,
    ERROR_402 = 402,
    ERROR_403 = 403,
    ERROR_404 = 404,
    ERROR_405 = 405,
    ERROR_406 = 406,
    ERROR_407 = 407,
    ERROR_408 = 408,
    ERROR_409 = 409,
    ERROR_410 = 410,
    ERROR_411 = 411,
    ERROR_412 = 412,
    ERROR_413 = 413,
    ERROR_414 = 414,
    ERROR_415 = 415,
    ERROR_416 = 416,
    ERROR_417 = 417,
    ERROR_418 = 418,
    ERROR_421 = 421,
    ERROR_422 = 422,
    ERROR_423 = 423,
    ERROR_424 = 424,
    ERROR_425 = 425,
    ERROR_426 = 426,
    ERROR_428 = 428,
    ERROR_429 = 429,
    ERROR_431 = 431,
    ERROR_451 = 451,
    UNKNOWN_ERROR = -1
};

struct LogError
{
    HTTPError error;
    string username;
};

// core functions
HTTPError *promptForErrorCodes(int numberOfErrors);
LogError *promptForErrorLogs(int numberOfLogs);

// helper functions
bool isErrorCodeValid(int errorCode);
string getErrorDescription(HTTPError errorCode);
string parseErrorMessage(HTTPError errorCode);

// constants
const int NUMBER_OF_LOGS = 5;
const HTTPError CODE_TO_OUTPUT = ERROR_429;

int main()
{
    // prompt user for number of error codes
    int numberOfErrors;
    cout << "Enter number of errors: " << endl;
    cout << "--> ";
    cin >> numberOfErrors;
    cout << "\n################\n\n";

    // prompt user for error codes
    HTTPError *errors = promptForErrorCodes(numberOfErrors);

    // initialize array of processed errors
    HTTPError *processedErrors = new HTTPError[numberOfErrors];
    int processedErrorsIndex = 0;
    bool hasRepeated = false;

    // print repeated errors
    cout << "Repeated errors: " << endl;
    for (int i = 0; i < numberOfErrors; i++)
    {
        for (int j = i + 1; j < numberOfErrors; j++)
        {
            // check if error is already processed and printed
            bool isProcessed = false;
            for (int k = 0; k < processedErrorsIndex; k++)
            {
                if (errors[i] == processedErrors[k])
                {
                    isProcessed = true;
                    break;
                }
            }

            // check if error is repeated and not processed
            if (errors[i] == errors[j] && !isProcessed)
            {
                // print error message
                cout << parseErrorMessage(errors[i]) << endl;
                // add error to processed errors
                hasRepeated = true;
                processedErrors[processedErrorsIndex] = errors[i];
                processedErrorsIndex++;
            }
        }
    }

    // print message if no repeated errors
    if (!hasRepeated)
    {
        cout << "- No repeated errors" << endl;
    }

    cout << "\n################\n\n";

    // prompt user for log errors
    LogError *loggedErrors = promptForErrorLogs(NUMBER_OF_LOGS);
    bool hasErrorsWithCodeToOutput = false;

    // print errors with code to output
    cout << "Users with error code " << to_string(CODE_TO_OUTPUT) << ":" << endl;
    for (int i = 0; i < 5; i++)
    {
        if (loggedErrors[i].error == CODE_TO_OUTPUT)
        {
            cout << "- Username: " << loggedErrors[i].username << endl;
            hasErrorsWithCodeToOutput = true;
        }
    }

    // print message if no errors with code to output
    if (!hasErrorsWithCodeToOutput)
    {
        cout << "- No users with this error code" << endl;
    }

    return 0;
}

// function that gets error code and returns error description
string getErrorDescription(HTTPError errorCode)
{
    switch (errorCode)
    {
    case 400:
        return "Bad Request";
    case 401:
        return "Unauthorized";
    case 402:
        return "Payment Required";
    case 403:
        return "Forbidden";
    case 404:
        return "Not Found";
    case 405:
        return "Method Not Allowed";
    case 406:
        return "Not Acceptable";
    case 407:
        return "Proxy Authentication Required";
    case 408:
        return "Request Timeout";
    case 409:
        return "Conflict";
    case 410:
        return "Gone";
    case 411:
        return "Length Required";
    case 412:
        return "Precondition Failed";
    case 413:
        return "Payload Too Large";
    case 414:
        return "URI Too Long";
    case 415:
        return "Unsupported Media Type";
    case 416:
        return "Range Not Satisfiable";
    case 417:
        return "Expectation Failed";
    case 418:
        return "I'm a teapot"; // 1998 April Fools' Day joke :)
    case 421:
        return "Misdirected Request";
    case 422:
        return "Unprocessable Entity";
    case 423:
        return "Locked";
    case 424:
        return "Failed Dependency";
    case 425:
        return "Too Early";
    case 426:
        return "Upgrade Required";
    case 428:
        return "Precondition Required";
    case 429:
        return "Too Many Requests";
    case 431:
        return "Request Header Fields Too Large";
    case 451:
        return "Unavailable For Legal Reasons";
    default:
        return "Unknown";
    }
}

// function that parse error message
string parseErrorMessage(HTTPError errorCode)
{
    return "Error" + to_string(errorCode) + " - " + getErrorDescription(errorCode);
}

// function that converts integer to HTTPError enum
HTTPError intToHTTPError(int errorCode)
{
    // check if errorCode exists in enum
    if (isErrorCodeValid(errorCode))
    {
        // if exists, return it as HTTPError
        return static_cast<HTTPError>(errorCode);
    }
    else
    {
        // if not, return UNKNOWN_ERROR
        return UNKNOWN_ERROR;
    }
}

// function that validates error code
bool isErrorCodeValid(int errorCode)
{
    return errorCode >= 400 &&
           errorCode <= 451 &&
           errorCode != 419 &&
           errorCode != 420 &&
           errorCode != 427 &&
           errorCode != 430 &&
           (errorCode <= 431 || errorCode == 451);
}

// function that prompts user for error codes and returns an array of HTTPError
HTTPError *promptForErrorCodes(int numberOfErrors)
{
    // create array of HTTPError
    HTTPError *errors = new HTTPError[numberOfErrors];

    // prompt user for error codes
    for (int i = 0; i < numberOfErrors; i++)
    {
        bool isValidated = false;
        while (!isValidated)
        {
            int errorCode;
            cout << "Enter error code (" << i + 1 << "):" << endl;
            cout << "--> ";
            cin >> errorCode;

            // check if error code is valid
            if (isErrorCodeValid(errorCode))
            {
                // if valid, convert it to HTTPError and add to array
                errors[i] = intToHTTPError(errorCode);
                isValidated = true;
                cout << "\n----------------\n\n";
            }
            else
            {
                // if not, print error message and prompt user again
                cout << "Error code is not valid. Please try again.\n"
                     << endl;
            }
        }
    }

    return errors;
}

// function that prompts user for error logs and returns an array of LogError
LogError *promptForErrorLogs(int numberOfLogs)
{
    LogError *errors = new LogError[numberOfLogs];

    for (int i = 0; i < numberOfLogs; i++)
    {
        cout << "Enter your username:" << endl;
        cout << "--> ";
        cin >> errors[i].username;
        cout << endl;

        bool isValidated = false;
        while (!isValidated)
        {
            int errorCode;
            cout << "Enter error code (" << i + 1 << "):" << endl;
            cout << "--> ";
            cin >> errorCode;

            // check if error code is valid
            if (isErrorCodeValid(errorCode))
            {
                // if valid, convert it to HTTPError and add to array
                errors[i].error = intToHTTPError(errorCode);
                isValidated = true;
                cout << "\n----------------\n\n";
            }
            else
            {
                // if not, print error message and prompt user again
                cout << "Error code is not valid. Please try again.\n"
                     << endl;
            }
        }
    }
    return errors;
}
