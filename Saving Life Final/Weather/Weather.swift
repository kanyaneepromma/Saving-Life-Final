//
//  Weather.swift
//  Saving Life Final
//
//  Created by Kanyanee P on 20/4/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import Foundation


struct Weather: Codable {
    let cod: String?
    let city: City?
    let cnt: Int?
    let list: [List]?
    let message: Double?
}

struct City: Codable {
    let coord: Coord?
    let country, name: String?
    let id: Int?
}

struct Coord: Codable {
    let lon, lat: Double?
}

struct List: Codable {
    let dt: Int?
    let weather: [WeatherElement]?
    let main: MainClass?
    let clouds: Clouds?
    let wind: Wind?
    let dtTxt: String?
    let sys: Sys?
    
    enum CodingKeys: String, CodingKey {
        case dt, weather, main, clouds, wind
        case dtTxt = "dt_txt"
        case sys
    }
}

struct Clouds: Codable {
    let all: Int?
}

struct MainClass: Codable {
    let pressure, seaLevel, grndLevel, tempKf: Double?
    let humidity: Int?
    let tempMin, temp, tempMax: Double?
    
    enum CodingKeys: String, CodingKey {
        case pressure
        case seaLevel = "sea_level"
        case grndLevel = "grnd_level"
        case tempKf = "temp_kf"
        case humidity
        case tempMin = "temp_min"
        case temp
        case tempMax = "temp_max"
    }
}

struct Sys: Codable {
    let pod: Pod?
}

enum Pod: String, Codable {
    case d = "d"
    case n = "n"
}

struct WeatherElement: Codable {
    let description: Description?
    let main: MainEnum?
    let id: Int?
    let icon: String?
}

enum Description: String, Codable {
    case brokenClouds = "broken clouds"
    case clearSky = "clear sky"
    case fewClouds = "few clouds"
    case overcastClouds = "overcast clouds"
    case scatteredClouds = "scattered clouds"
}

enum MainEnum: String, Codable {
    case clear = "Clear"
    case clouds = "Clouds"
}

struct Wind: Codable {
    let speed, deg: Double?
}



