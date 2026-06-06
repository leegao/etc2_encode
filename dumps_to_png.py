import os
import re
from pathlib import Path

from PIL import Image


def convert_rgba_bin_to_png(target_directory="."):
    path = Path(target_directory)
    file_pattern = "*_fmt_37_*x*.bin"
    regex_pattern = re.compile(r"_fmt_37_(\d+)x(\d+)\.bin$")

    count = 0
    for i, file_path in enumerate(path.glob(file_pattern)):
        match = regex_pattern.search(file_path.name)
        if not match:
            continue

        width = int(match.group(1))
        height = int(match.group(2))
        output_path = file_path.with_suffix(".png")

        try:
            raw_bytes = file_path.read_bytes()
            expected_size = width * height * 4
            if len(raw_bytes) != expected_size:
                print(
                    f"Error: {file_path.name} ({len(raw_bytes)}) does not match expected size {expected_size}."
                )
                continue

            image = Image.frombytes("RGBA", (width, height), raw_bytes, "raw", "RGBA")
            image = image.transpose(Image.FLIP_TOP_BOTTOM)
            image.save(output_path)
            print(f"Converted [{i}] {output_path.name} ({width}x{height})")
            count += 1

        except Exception as e:
            print(f"Error: {e}")


if __name__ == "__main__":
    convert_rgba_bin_to_png("dumps")
