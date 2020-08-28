//
//  main.swift
//  Genic
//
//  Created by huayf on 2020/8/25.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Foundation

//https://github.com/raywenderlich/swift-algorithm-club/tree/master/Genetic


extension String {
  
  var unicodeArray: [UInt8] {
    return [UInt8](self.utf8)
  }
}

let lex: [UInt8] = " !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~".unicodeArray

// This is the end goal and what we will be using to rate fitness. In the real world this will not exist
let OPTIMAL:[UInt8] = "Hello world!".unicodeArray

// The length of the string in our population. Organisms need to be similar
let DNA_SIZE = OPTIMAL.count

// 每一代的数量
let POP_SIZE = 50

// 迭代次数
let GENERATIONS = 5000

// The chance in which a random nucleotide can mutate (1/n)
// 核苷酸的突变概率 1/chance
let MUTATION_CHANCE = 100

//1.初始化人群
func randomPopulation(from lexicon: [UInt8], populationSize: Int, dnaSize: Int) -> [[UInt8]] {
  var pop = [[UInt8]]()
  
  (0..<populationSize).forEach { _ in
    var dna = [UInt8]()
    (0..<dnaSize).forEach { _ in
      let char = lexicon.randomElement()!
      dna.append(char)
    }
    pop.append(dna)
  }
  return pop
}
//2.选择
//2.1计算适应度 越小越好 相当于计算Lost
func calculateFitness(dna: [UInt8], optimal: [UInt8]) -> Int {
  var fitness = 0
  for index in dna.indices {
    fitness += abs(Int(dna[index]) - Int(optimal[index]))
  }
  return fitness
}

//2.2轮盘选择
// weight: 和适应度成反比，适应度越小 weight越大  范围在(0, 1]
func weightedChoice(items: [(dna: [UInt8], weight: Double)]) -> (dna: [UInt8], weight: Double) {
  
  let total = items.reduce(0) { $0 + $1.weight }
  var n = Double.random(in: 0..<(total * 1000000)) / 1000000.0
  for item in items {
    if n < item.weight {  //选取第一个权重大于n的
      return item
    }
    n = n - item.weight
  }
  return items[1]
}

//3.突变
//mutationChance：突变因子， 在这里表示为每个基因有1/mutationChance概率会突变
func mutate(lexicon: [UInt8], dna: [UInt8], mutationChance: Int) -> [UInt8] {
  var outputDna = dna
  (0..<dna.count).forEach { i in
    let rand = Int.random(in: 0..<mutationChance)
    if rand == 1 {
      outputDna[i] = lexicon.randomElement()!
    }
  }
  
  return outputDna
}

//4.交叉
func crossover(dna1: [UInt8], dna2: [UInt8], dnaSize: Int) -> [UInt8] {
  let pos = Int.random(in: 0..<dnaSize)
  
  let dna1Index1 = dna1.index(dna1.startIndex, offsetBy: pos)
  let dna2Index1 = dna2.index(dna2.startIndex, offsetBy: pos)
  
  return [UInt8](dna1.prefix(upTo: dna1Index1) + dna2.suffix(from: dna2Index1))
}



/*####################################################################################
 #                                                                                    #
 #                                     开始测试                                         #
 #                                                                                    #
 ####################################################################################*/


//初始化人群
var population: [[UInt8]] = randomPopulation(from: lex, populationSize: POP_SIZE, dnaSize: DNA_SIZE)
var fittest = population[0]

func main() {
  for generation in 0...GENERATIONS {
    var weightedPopulation = [(dna: [UInt8], weight: Double)]()
    //计算每个个体的权重
    for individual in population {
      let fitnessValue = calculateFitness(dna: individual, optimal: OPTIMAL)
      let pair = (individual, fitnessValue == 0 ? 1.0 : 1.0/Double(fitnessValue))
      weightedPopulation.append(pair)
    }
    
    population = []
    
    //随机选出两个个体进行繁衍，进行POP_SIZE次， 产生的新一代替换掉当前的这一代
    (0...POP_SIZE).forEach { _ in
      let ind1 = weightedChoice(items: weightedPopulation)
      let ind2 = weightedChoice(items: weightedPopulation)
      //交叉
      let offspring = crossover(dna1: ind1.dna, dna2: ind2.dna, dnaSize: DNA_SIZE)
      //概率性突变
      population.append(mutate(lexicon: lex, dna: offspring, mutationChance: MUTATION_CHANCE))
    }
    
    fittest = population[0]
    var minFitness = calculateFitness(dna: fittest, optimal: OPTIMAL)
    
    //选拔出最优秀的个体
    population.forEach { indv in
      let indvFitness = calculateFitness(dna: indv, optimal: OPTIMAL)
      if indvFitness < minFitness {
        fittest = indv
        minFitness = indvFitness
      }
    }
    
    if minFitness == 0 { break }
    print("\(generation): \(String(bytes: fittest, encoding: .utf8)!)")
  }
  print("fittest string: \(String(bytes: fittest, encoding: .utf8)!)")
}
//main()


