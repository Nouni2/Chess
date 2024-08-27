import os

def generate_layout(directory, output_file, indent_level=0):
    indent = ' ' * 4 * indent_level
    for item in os.listdir(directory):
        item_path = os.path.join(directory, item)
        if os.path.isdir(item_path):
            output_file.write(f"{indent}{item}/\n")
            generate_layout(item_path, output_file, indent_level + 1)
        else:
            output_file.write(f"{indent}{item}\n")

def main():
    # Use the current working directory
    directory = os.getcwd()
    output_file_path = "directory_layout.txt"

    # Open the file with UTF-8 encoding
    with open(output_file_path, "w", encoding="utf-8") as output_file:
        generate_layout(directory, output_file)

    print(f"Directory layout has been saved to {output_file_path} in {directory}")

if __name__ == "__main__":
    main()
