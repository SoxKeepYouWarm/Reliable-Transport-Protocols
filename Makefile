.PHONY: clean All

All:
	@echo "----------Building project:[ cse489_pa2 - Debug ]----------"
	@"$(MAKE)" -f  "cse489_pa2.mk"
clean:
	@echo "----------Cleaning project:[ cse489_pa2 - Debug ]----------"
	@"$(MAKE)" -f  "cse489_pa2.mk" clean
