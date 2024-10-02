// INTERFASE SEGREGATION PRINCIPAL (ISP)
#include <vector>
struct Document;

// At firts, we may just have a interface with all features
/*
struct IMachine
{
 virtual void print(Document& doc) = 0;
 virtual void fax(Document& doc) = 0;
 virtual void scan(Document& doc) = 0;
};
*/

// with this methology, we always have an implementation like this
/*
struct MFP : IMachine
{
 void print(Document& doc) override;
 void fax(Document& doc) override;
 void scan(Document& doc) override;
};
*/

// PROBLEMS you should have:
// 1. Recompile
// 2. Client does not need this
// 3. Forcing implementors to implement too much


// Better aproach is to have a independ interface 
// for each feature that we need to use

// A interface for printer
struct IPrinter {
  virtual void print(Document& doc) = 0;
};

// An interface for scanner
struct IScanner {
  virtual void scan(Document& doc) = 0;
};

// The printer implementation
struct Printer : IPrinter {
  void print(Document& doc) override;
};

// The scanner implementation
struct Scanner : IScanner {
  void scan(Document& doc) override;
};

// An interface that configure both previous features
struct IMachine: IPrinter, IScanner {
};

// The implementation with both features 
struct Machine : IMachine {
  IPrinter& printer;
  IScanner& scanner;

  Machine(IPrinter& printer, IScanner& scanner) : printer{printer}, scanner{scanner} {
  }

  void print(Document& doc) override {
    printer.print(doc);
  }

  void scan(Document& doc) override;
};

// IPrinter --> Printer
// everything --> Machine