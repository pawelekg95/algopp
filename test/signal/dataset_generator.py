#!/bin/python3
import json
import argparse
import scipy.signal
from scipy.fft import fft
import numpy
from typing import List, Tuple


class NpEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, numpy.integer):
            return int(obj)
        if isinstance(obj, numpy.floating):
            return float(obj)
        if isinstance(obj, numpy.ndarray):
            return obj.tolist()
        return super(NpEncoder, self).default(obj)


def dump(distance: float = 0,
         height: float = 0,
         dataset: List[float] = None,
         peaks_list: List[Tuple[float, float]] = None,
         path: str = None,
         fourier: List[complex] = None,
         peaks_type: str = None):
    json_object = {
        "height": height,
        "distance": distance,
        "dataset": dataset,
        "peaks": [(x, dataset[x]) for x in peaks_list],
        "fourier": [(x.real, x.imag) for x in fourier],
        "peaks_type": peaks_type
    }
    with open(path, "w") as file:
        json.dump(json_object, file, cls=NpEncoder)


def generate_dataset(size: int = 0) -> List[float]:
    return [x[0] for x in list(numpy.random.rand(size, 1))]


def peaks(dataset: List[float] = None, distance: float = 0, height: float = 0, peak_type: str = '')\
        -> List[Tuple[float, float]]:
    tmp = dataset.copy()
    if peak_type == 'low':
        tmp = [1/x for x in tmp]
        height = [0, 1/height] if height != 0 else height
    return list(scipy.signal.find_peaks(x=tmp, height=height, distance=distance)[0])


def fourier(dataset: List[float] = None) -> List[float]:
    tmp = dataset.copy()
    return fft(tmp)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--path', dest='path', required=True)
    parser.add_argument('-s', '--size', dest='size', required=True, type=int)
    parser.add_argument('--height', dest='height', required=True, type=float)
    parser.add_argument('-d', '--distances', dest='dist', required=True, type=float)
    parser.add_argument('-t', '--type', dest='type', required=True, type=str, choices=['high', 'low'])
    args = parser.parse_args()
    dataset = generate_dataset(args.size)
    peaks_list = peaks(dataset, distance=args.dist, height=args.height, peak_type=args.type)
    transformed = fourier(dataset)
    dump(args.dist, height=args.height, dataset=dataset, peaks_list=peaks_list, path=args.path, fourier=transformed, peaks_type=args.type)
