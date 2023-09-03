#include "20180492.h"

int main() {
	//file open
	FILE* maze = fopen("maze.maz", "w");
	if (maze == NULL) {
		printf("File open failure!\n");
		_Exit(0);
	}

	srand((unsigned int)time(NULL));

	// input height and width of maze
	int height, width, x, y, i;
	scanf("%d", &width);
	scanf("%d", &height);

	// dynamic memory allocation for constructing maze
	vertex** line = (vertex**)malloc(sizeof(struct vertex *) * height);
	for (y = 0; y < height; y++) {
		line[y] = (vertex*)malloc(sizeof(struct vertex) * width);
	}

	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			line[y][x].down = 1;
			line[y][x].right = 1;
			line[y][x].set = 0;
		}
	}

	// construct maze
	for (y = 0; y < height - 1; y++) {
		for (x = 0; x < width; x++) {
			if (!line[y][x].set) {
				line[y][x].set = (y * width) + x + 1;
			}
		}
		for (x = 0; x < width - 1; x++) {
			int uni = rand() % 2;
			if (uni && line[y][x].set != line[y][x + 1].set) {
				line[y][x].right = 0;
				if (line[y][x].set > line[y][x + 1].set)
					line[y][x].set = line[y][x + 1].set;
				else
					line[y][x + 1].set = line[y][x].set;
				if (y) {
					for (int k = 0; k < width; k++) {
						if (!line[y - 1][k].down && line[y][k].set < line[y - 1][k].set) {
							int p = line[y - 1][k].set;
							for (i = 0; i < width; i++) {
								for (int j = y; j >= 0; j--) {
									if (line[j][i].set == p) {
										line[j][i].set = line[y][k].set;
									}
								}
							}
						}
					}
				}
			}
		}
		
		int ind = 0, start = 0;
		int min = height * width;
		while (1) {
			if (!line[y][ind].right) {
				if (line[y][ind].set < min) {
					min = line[y][ind].set;
				}
				ind++;
			}
			else {
				if (line[y][ind].set < min) {
					min = line[y][ind].set;
				}
				for (i = start; i <= ind; i++) {
					line[y][i].set = min;
				}
				ind++;
				min = height * width;
				start = ind;
			}
			if (ind == width - 1) {
				if (line[y][ind].set < min) {
					min = line[y][ind].set;
				}
				for (i = start; i <= ind; i++) {
					line[y][i].set = min;
				}
				break;
			}
		}

		if (y) {
			for (int k = 0; k < width; k++) {
				if (!line[y - 1][k].down && line[y][k].set < line[y - 1][k].set) {
					int p = line[y - 1][k].set;
					for (i = 0; i < width; i++) {
						for (int j = y; j >= 0; j--) {
							if (line[j][i].set == p) {
								line[j][i].set = line[y][k].set;
							}
						}
					}
				}
			}
		}
		
		for (x = 0; x < width; x++) {
			int downward = rand() % 2;
			if (downward) {
				line[y][x].down = 0;
				line[y + 1][x].set = line[y][x].set;
			}
		}
		for (x = 0; x < width; x++) {
			int flag = 0;
			for (i = 0; i < width; i++) {
				if (line[y][x].set == line[y][i].set && !line[y][i].down) {
					flag = 1;
					break;
				}
			}
			if (!flag) {
				line[y][x].down = 0;
				line[y + 1][x].set = line[y][x].set;
			}
		}
	}
	int h = height - 1;
	for (x = 0; x < width; x++) {
		if (!line[h][x].set) {
			line[h][x].set = (h * width) + x + 1;
		}
	}

	for (x = 0; x < width; x++) {
		if (!line[h - 1][x].down && line[h][x].set < line[h - 1][x].set) {
			int p = line[h - 1][x].set;
			for (i = 0; i < width; i++) {
				for (int j = h; j >= 0; j--) {
					if (line[h][i].set == p) {
						line[h][i].set = line[h][x].set;
					}
				}
			}
		}
	}
	
	int ind = 0, start = 0;
	int min = height * width;
	while (1) {
		if (!line[y][ind].right) {
			if (line[y][ind].set < min) {
				min = line[y][ind].set;
			}
			ind++;
		}
		else {
			if (line[y][ind].set < min) {
				min = line[y][ind].set;
			}
			for (i = start; i <= ind; i++) {
				line[y][i].set = min;
			}
			ind++;
			min = height * width;
			start = ind;
		}
		if (ind == width - 1) {
			if (line[y][ind].set < min) {
				min = line[y][ind].set;
			}
			for (i = start; i <= ind; i++) {
				line[y][i].set = min;
			}
			break;
		}
	}
	int one_flag = 0, next_flag = 0;
	for (x = 0; x < width - 1; x++) {
		if (line[h][x].set != line[h][x + 1].set) {
			
			if (x && line[h][x - 1].set != line[h][x].set && line[h][x - 1].set == line[h][x + 1].set) {
				continue;
			}
			if (next_flag && one_flag) {
				if (one_flag && (line[h][x + 1].set == 1)) { // line[h][x].set == 1 || 
					continue;
				}
			}
			else if (!next_flag && one_flag) {
				next_flag++;
			}
			int same_num_flag = 0;
			for (i = x - 1; i >= 0; i--) {
				if (line[h][x + 1].set == line[h][i].set) {
					same_num_flag = 1;
					break;
				}
			}
			if (same_num_flag) {
				continue;
			}
			line[h][x].right = 0;
			if (!one_flag && line[h][x].set == 1 || line[h][x + 1].set == 1) { // !one_flag && line[h][x].set == 1 ||
				one_flag++;
			}
		}
	}

	/* debug maze set
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			printf("%3d", line[y][x].set);
		}
		printf("\n");
	}
	*/

	//draw maze
	for (x = 0; x < (width * 2) + 1; x++) {
		if (!(x % 2)) fprintf(maze, "+");
		else fprintf(maze, "-");
		if (x == width * 2) fprintf(maze, "\n");
	}
	for (y = 0; y < height; y++) {
		fprintf(maze, "|");
		for (x = 0; x < width - 1; x++) {
			if (!line[y][x].right) {
				fprintf(maze, "  ");
			}
			else fprintf(maze, " |");
		}
		fprintf(maze, " |\n");
		fprintf(maze, "+");
		for (x = 0; x < width; x++) {
				if (!line[y][x].down) fprintf(maze, " +");
				else fprintf(maze, "-+");
		}
		fprintf(maze, "\n");
	}

	// file close
	fclose(maze);

	// free allocated memory for maze array
	for (y = 0; y < height; y++) {
		free(line[y]);
	}
	free(line);

	/*
	// debug constructed maze
	FILE* Debug = fopen("maze.maz", "r");
	char debug_str[201];
	for (y = 0; y < (height * 2) + 1; y++) {
		fgets(debug_str, 200, Debug);
		printf("%s", debug_str);
	}
	fclose(Debug);
	*/

	return 0;
}