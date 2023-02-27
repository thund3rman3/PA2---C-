BUILD = bin
SRC = src
BINARY = prettyprinter

all:
	@mkdir -p $(BUILD)
	@$(CXX) $(SRC)/main.cpp -o $(BUILD)/$(BINARY) -Wall -pedantic -std=c++11
	@echo "Finished."

clean:
	@rm -r ./$(BUILD)
	@echo "Cleaned."

run:
	@./$(BUILD)/$(BINARY)
