CFLAGS =                 \
	-O3                    \
	-Wall                  \
	-Wextra                \
	-Werror                \
	-std=c89               \
	-pedantic              \
	-Wmissing-prototypes   \
	-Wstrict-prototypes    \
	-Wold-style-definition \

ALL_H = $(wildcard src/framework/*.h) $(wildcard src/executables/*.h)
ALL_FRAMEWORK_O = $(addprefix obj/framework/, $(addsuffix .o, $(basename $(notdir $(wildcard src/framework/*.c)))))
ALL_EXECUTABLES = $(addprefix $(SDF_EXECUTABLE_PREFIX), $(basename $(notdir $(wildcard src/executables/*.c))))
ALL_TEST_FRAMEWORK = $(wildcard test/framework/*.bash)
ALL_TEST_RESULTS = $(addprefix test_results/, $(basename $(notdir $(wildcard test/executables/*.bash))))
ALL_TEST_SDF = $(wildcard test/sdf/*.sdf)

obj/%.o: src/%.c $(ALL_H) makefile
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

$(SDF_EXECUTABLE_PREFIX)%: obj/executables/%.o $(ALL_FRAMEWORK_O)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ -lm

test_results/%: test/executables/%.bash $(ALL_EXECUTABLES) $(ALL_TEST_FRAMEWORK) $(ALL_TEST_SDF)
	mkdir -p test_results
	submodules/bats-core/bin/bats $<
	touch $@

.PHONY: all clean test

all: $(ALL_EXECUTABLES)

clean:
	rm -rf bin obj test_results

test: $(ALL_TEST_RESULTS)
