import asyncio
import os
from operator import truediv

import discord
import random
from dotenv import load_dotenv
import json

load_dotenv()
TOKEN = os.getenv('DISCORD_TOKEN')
intents = discord.Intents.default()
intents.message_content = True
client = discord.Client(intents=intents)

peak_gifs = ["https://tenor.com/view/is-this-peak-gif-11323509234146738166",
             "https://tenor.com/view/gohan-its-so-peak-gohan-crying-gohan-its-so-peak-peak-gif-11211568239007237362"]

options = "Options:\n!give <amount> @user - Pay a certain amount to a user\n!wheel <bet> - Spin the wheel for a chance to win 6x your money if all 3 fruits match, or 1.5x your money if 2 fruits match\n!balance - Check your current balance\n!work - Answer questions to earn money\n!casino - Show casino's total profit\n!leaderboard - Show the balances of all users, sorted by amount earned\n!rob @user - Attempt to rob a user\n!help - Show the options menu"

wheel = ["🍎", "🍊", "🍓", "🍌", "🍉"]

balances = {}
casino_profit = 0
work_questions = {}

questions = [
    ("What is 12 * 13?", "156", 10),
    ("What is 17^2?", "289", 15),
    ("In Java, what keyword is used for inheritance?", "extends", 40),
    ("What sorting algorithm has average O(n log n)? Fill in the blank: _____ sort", "merge", 50),
    ("What keyword, in Java, represents that the method or field belongs to the class itself?", "static", 45),
    ("What is 9 * 14?", "126", 10),
    ("What data structure allows for adding elements?", "arraylist", 40),
    ("What is 15 * 15?", "225", 10),
    ("What is the square root of 144?", "12", 10),
    ("What is the value of this expression? !(p || q) && r", "!p && !q && r", 45),
    ("If a doctor gives you 3 pills and tells you to take one every half hour, how many hours will they last? Answer with a number: ___ hour(s)",
     "1", 35),
    ("What is the result of ""(double) (1 / 4)""", "0.0", 30),
]


def get_balance(user_id):
    if user_id not in balances:
        balances[user_id] = 0
    return balances[user_id]


async def send_peak(message):
    await message.channel.send(random.choice(peak_gifs))


async def send_help(message):
    await message.channel.send(options)


async def show_balance(message):
    await message.channel.send(f"{message.author.mention} has ${get_balance(message.author.id)}")


async def work(message):
    question = random.choice(questions)

    work_questions[message.author.id] = {"answer": question[1].lower(), "reward": question[2]}
    await message.channel.send(f"Work question:\n{question[0]}")


async def spin_wheel(message, bet):
    global casino_profit
    user_id = message.author.id

    if bet <= 0:
        await message.channel.send("Bet a larger amount\n")
        await show_balance(message)
        return

    if get_balance(user_id) < bet:
        await message.channel.send("Not enough money.")
        await show_balance(message)
        return

    balances[user_id] -= bet
    casino_profit += bet

    msg = await message.channel.send("🎰Spinning the wheel...")
    for i in range(5):
        temp = [random.choice(wheel), random.choice(wheel), random.choice(wheel)]

        await msg.edit(content="🎰 " + " ".join(temp))
        await asyncio.sleep(0.2)

    result = [random.choice(wheel), random.choice(wheel), random.choice(wheel)]
    display = " ".join(result)

    if result[0] == result[1] == result[2]:
        won = bet * 6
        balances[user_id] += won
        casino_profit -= won
        await msg.edit(content=f"🎰 {display}\n💰Jackpot!! +${won - bet}")
    elif (result[0] == result[1]) or (result[1] == result[2]) or (result[2] == result[0]):
        won = int(bet * 1.5)
        balances[user_id] += won
        casino_profit -= won
        await msg.edit(content=f"🎰 {display}\n💰Two of a kind! +${won - bet}")
    else:
        await msg.edit(content=f"🎰 {display}\n❌You lost ${bet}...")


async def check_work(message):
    user_id = message.author.id

    if user_id not in work_questions:
        return False

    data = work_questions[user_id]

    if message.content.lower().strip() == data["answer"]:
        balances[user_id] = (get_balance(user_id) + data["reward"])

        await message.channel.send(
            f"✅ Correct! You earned ${data['reward']}"
        )

        del work_questions[user_id]

        return True

    return False


async def handle_wheel(message):
    if not message.content.startswith("!wheel"):
        return False

    temp = message.content.split()

    if len(temp) != 2:
        await message.channel.send("Wrong usage. !wheel <bet>")
        return True

    if not temp[1].isdigit():
        await message.channel.send("Enter a number")
        return True

    await spin_wheel(message, int(temp[1]))

    return True


async def show_casino_balance(message):
    if casino_profit > 0:
        await message.channel.send(f"Casino has earned: ${casino_profit}")
    elif casino_profit < 0:
        await message.channel.send(f"Casino has lost: ${casino_profit}")
    else:
        await message.channel.send(f"Casino has made no money.")


async def show_leaderboard(message):
    if len(balances) == 0:
        await message.channel.send("Nobody has any money yet.")
        return

    leaderboard = []

    for i in balances:
        leaderboard.append([balances[i], i])

    leaderboard.sort()

    msg = "🏆 Leaderboard\n"
    place = 1

    for i in range(len(leaderboard) - 1, -1, -1):
        balance = leaderboard[i][0]
        id = leaderboard[i][1]

        user = await client.fetch_user(id)
        msg += f"{place}. {user.name}: ${balance}\n"

        place += 1

    await message.channel.send(msg)


async def rob(message):
    if len(message.mentions) != 1:
        await message.channel.send("Wrong usage. !rob @user")
        return

    victim = message.mentions[0]

    if victim.id == message.author.id:
        await message.channel.send("You cannot rob yourself.")
        return

    if get_balance(victim.id) < 50:
        await message.channel.send("That person is too poor to rob. Try to rob someone with at least $50.")
        return

    if get_balance(message.author.id) < 50:
        await message.channel.send(
            "You are too poor to pay the minimum fine if you get caught. Earn at least $50 to ensure you do not get prison time.")
        return

    stolen = random.randint(
        max(1, (get_balance(victim.id) // 10)),
        max(1, (get_balance(victim.id) // 4))
    )

    if random.random() <= 0.7:

        balances[victim.id] -= stolen
        balances[message.author.id] += stolen

        await message.channel.send(f"💰 {message.author.mention} robbed {victim.mention} and stole ${stolen}!")
    else:
        fine = min(int(stolen * 2.5), get_balance(message.author.id))

        balances[message.author.id] -= fine
        balances[victim.id] += fine

        await message.channel.send(f"🚔 {message.author.mention} got caught and paid {victim.mention} ${fine}.")


async def give(message, amount):
    if len(message.mentions) != 1:
        await message.channel.send("Wrong usage. !give <amount> @user")
        return False

    receiver = message.mentions[0]

    if receiver.id == message.author.id:
        await message.channel.send("You cannot send money to yourself.")
        return False

    if get_balance(message.author.id) < amount:
        await message.channel.send(
            "You do not have enough money.")
        await show_balance(message)
        return False

    balances[message.author.id] -= amount
    balances[receiver.id] += amount

    await message.channel.send(f"💸 Success! {message.author.mention} sent ${amount} to {receiver.mention}.")
    return True


async def handle_giving(message):
    if not message.content.startswith("!give"):
        return False

    temp = message.content.split()

    if len(temp) != 3:
        await message.channel.send("Wrong usage. !give <amount> @user")
        return True

    if not temp[1].isdigit():
        await message.channel.send("Enter a number")
        return True

    await give(message, int(temp[1]))
    return True


def save_balances():
    data = {
        "balances": balances,
        "casino_profit": casino_profit
    }

    with open("casino.json", "w") as f:
        json.dump(data, f, indent=4)


def load_balances():
    global balances
    global casino_profit

    if os.path.exists("casino.json"):
        with open("casino.json", "r") as f:
            data = json.load(f)

        balances = {}

        for i in data["balances"]:
            balances[int(i)] = data["balances"][i]

        casino_profit = data["casino_profit"]


@client.event
async def on_ready():
    print(f'{client.user} has connected to Discord!')


@client.event
async def on_message(message):
    if message.author == client.user:
        return

    if await check_work(message):
        save_balances()
        return

    if await handle_wheel(message):
        save_balances()
        return

    if await handle_giving(message):
        save_balances()
        return

    if "peak" in message.content.lower():
        await send_peak(message)

    if "!help" == message.content.lower():
        await send_help(message)

    if "!balance" == message.content.lower():
        await show_balance(message)

    if "!work" == message.content.lower():
        await work(message)

    if "!casino" == message.content.lower():
        await show_casino_balance(message)

    if "!leaderboard" == message.content.lower():
        await show_leaderboard(message)

    if "!rob" in message.content.lower():
        await rob(message)

    save_balances()


load_balances()
client.run(TOKEN)
