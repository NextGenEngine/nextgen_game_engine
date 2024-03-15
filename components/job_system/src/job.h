class Job {
 public:
  virtual void execute() = 0;  // Pure virtual function making Job an interface
  virtual ~Job() = default;    // Virtual destructor for proper cleanup
};
