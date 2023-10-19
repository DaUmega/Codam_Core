<template>
  <div class="gamecentre">
    <div>
      <div v-if="!inQueue && !inGame && isLoggedIn">
        <div class="button-container">
          <CustomButton
          class="custom-button orange-button"
          :handleClick="standardGameMode"
          >
          Play Original
          </CustomButton>
          <CustomButton
          class="custom-button rainbow-button"
          :handleClick="standardGameMode"
          @click="handleBeBraveClick()"
          >
          Be Disco!
          </CustomButton>
          <CustomButton
          class="custom-button zebra-button"
          :handleClick="standardGameMode"
          @click="handleZebraClick()"
          >
          Be Techno!
          </CustomButton>
      </div>
      <div class="button-container">
          <CustomButton
          class="custom-button rainbow-button"
          :handleClick="freemoveGameMode"
          @click="handleBeEssamClick()"
          >
          Free Move
        </CustomButton>
      </div>
    </div>
    <div v-else-if="inQueue">
    <WaitingAnimation />
    </div>
  </div>
</div>
<div>
  <canvas
  id="canvas-element"
  class="canvas"
  :class="{ 'canvas-add': showCanvasAdd }"
  width="1400"
  height="800"
  style="border: 0px solid #ABCDEF;"
  />
</div>
</template>

<script lang="ts">
import { defineComponent } from 'vue'
import CustomButton from '../components/general/CustomButton.vue'
import WaitingAnimation from '../components/game/WaitingAnimation.vue'
import SocketioService from '@/services/socketio.service'
import { CurrentGameState, GameMode } from '../utils/game-definitions'
// import { UsersService } from '@/users/users.service';
import { API } from '@/plugins/axios'
import { useToast } from 'vue-toastification'

export default defineComponent({
  components: {
    WaitingAnimation,
    CustomButton
  },
  data () {
    return {
      showCanvasAdd: false,
      isZebraClicked: false,
      isBeBraveClicked: false,
      isBeEssamClicked: false,
      buttonClicked: false,
      selectGameMode: false,
      gameMode: GameMode.NO_MATCH,
      inQueue: false,
      userId: -1,
      gameId: -1,
      activeUser: sessionStorage.getItem('activeuser') || '',
      inGame: false,
      arrowUp: false,
      arrowDown: false,
      arrowLeft: false,
      arrowRight: false,
      connection: new SocketioService(),
      namePlayer1: '',
      namePlayer2: '',
      isLoggedIn: false
    }
  },
  async created () {
    if (this.activeUser) {
      this.isLoggedIn = true
      await API.get(`updateUserActivity/${this.activeUser}/1`)
    }
    try {
      const response = await API.get(`login?user=${this.activeUser}`, {
        headers: {
          'Content-Type': 'application/json'
        }
      })

      this.userId = response.data.id
      console.log('userId:', this.userId)
    } catch (error) {
      console.error('Search Button Error:', error)
    }
  },
  async mounted () {
    await this.$nextTick()
    const toast = useToast()
    const gettingChallenged = sessionStorage.getItem('challenge')
    if (gettingChallenged) {
      toast.info('Challenge Accepted! Please choose a game mode!')
      sessionStorage.removeItem('challenge')
    }
    const canvas: HTMLCanvasElement = document.getElementById('canvas-element') as HTMLCanvasElement
    const ctx: CanvasRenderingContext2D = canvas.getContext('2d') as CanvasRenderingContext2D
    this.connection.setupSocketConnection('/gamescreen')
    console.log('connection:', this.connection)

    // emit the default gameStatuse before the game starts.
    while (this.userId === -1) {
      await new Promise(resolve => setTimeout(resolve, 100))
      console.log('waiting for userId')
    }
    await API.get(`updateUserActivity/${this.activeUser}/3`)
    console.log('userId in GameScreen:', this.userId)
    this.connection.socket.emit('sendUserIdToGameRoom', this.userId)
    this.connection.socket.emit('CheckGameStatus', this.userId)
    this.connection.socket.on('GameStatus', (data: any) => {
      console.log('Received "GameStatus" event with data:', data)
      if (data.alreadyInGame === true) {
        this.namePlayer1 = data.namePlayer1
        this.namePlayer2 = data.namePlayer2
        this.gameId = data.gameId
        this.inGame = true
        this.inQueue = false
        console.log('connecting socket on GameStatus')
        this.listenToGame(ctx, canvas)
      } else if (data.alreadyInQueue) {
        this.inQueue = true
        this.inGame = false
        this.gameMode = data.gameMode
        console.log('Player already in Q')
      }
    })
    this.connection.socket.on('initGame', (data: any) => {
      this.connection.socket.emit('userConnected', this.userId)
      console.log('Received "GameStatus" event with data:', data)
      if (data.player1 === this.userId || data.player2 === this.userId) {
        this.namePlayer1 = data.namePlayer1
        this.namePlayer2 = data.namePlayer2
        this.gameId = data.gameId
        this.inGame = true
        this.inQueue = false
        console.log('connect socket on initGame')
        this.listenToGame(ctx, canvas)
      }
    })
    this.connection.socket.on('Winner', (winningUser: string) => {
      this.inGame = false

      this.drawEndScreen(ctx, canvas, winningUser)
      this.connection.socket.off('GameState')
    })
    document.addEventListener('keydown', this.keyDownEvent)
    document.addEventListener('keyup', this.keyUpEvent)
  },
  unmounted () {
    document.removeEventListener('keydown', this.keyDownEvent)
    document.removeEventListener('keyup', this.keyUpEvent)
    this.connection.socket.disconnect()
  },
  methods: {
    handleBeBraveClick () {
      this.isBeBraveClicked = true
    },
    handleDefaultGameClick () {
      this.buttonClicked = true
    },
    handleZebraClick () {
      this.isZebraClicked = true
    },
    handleBeEssamClick () {
      this.isBeEssamClicked = true
    },
    standardGameMode () {
      this.queueForGame('Standard')
    },
    freemoveGameMode () {
      this.queueForGame('OpenMove')
    },
    listenToGame (ctx: CanvasRenderingContext2D, canvas: HTMLCanvasElement) {
      // ctx.clearRect(0, 0, canvas.width, canvas.height)
      // get the position and current gamestate back from the server
      this.connection.socket.on('GameState', (data: any) => {
        const state: CurrentGameState = data
        this.drawGame(ctx, canvas, state)
      })
    },
    queueForGame (gameMode: string) {
      console.log('queueForGame method called with gameMode:', gameMode)
      var canvas: HTMLCanvasElement = document.getElementById('canvas-element') as HTMLCanvasElement
      var ctx: CanvasRenderingContext2D = canvas.getContext('2d') as CanvasRenderingContext2D
      this.gameMode = gameMode as GameMode
      this.inQueue = true

      // Send the server a request to be queued in the given game-mode's queue
      const packet = { gameMode: this.gameMode, userId: this.userId }
      console.log('inside queue for game')
      this.connection.socket.emit('QueueForGame', packet)
      console.log('Emitted "QueueForGame" event with packet:', packet)
    },
    keyDownEvent (e: KeyboardEvent) {
      if (this.userId === -1 || this.inGame === false) {
        return
      }

      const payload = { userId: this.userId, gameId: this.gameId, enabled: true, key: e.key }
      if (!this.arrowDown && e.key === 'ArrowDown') {
        this.connection.socket.emit('UpdatePaddleInput', payload)
        this.arrowDown = true
      } else if (!this.arrowUp && e.key === 'ArrowUp') {
        this.connection.socket.emit('UpdatePaddleInput', payload)
        this.arrowUp = true
      } else if (!this.arrowRight && e.key === 'ArrowRight') {
        this.connection.socket.emit('UpdatePaddleInput', payload)
        this.arrowRight = true
      } else if (!this.arrowLeft && e.key === 'ArrowLeft') {
        this.connection.socket.emit('UpdatePaddleInput', payload)
        this.arrowLeft = true
      }
    },

    keyUpEvent (e: KeyboardEvent) {
      if (this.userId === -1 || this.inGame === false) {
        return
      }

      const payload = { userId: this.userId, gameId: this.gameId, enabled: false, key: e.key }
      if (e.key === 'ArrowDown') {
        this.connection.socket.emit('UpdatePaddleInput', payload)
        this.arrowDown = false
      } else if (e.key === 'ArrowUp') {
        this.connection.socket.emit('UpdatePaddleInput', payload)
        this.arrowUp = false
      } else if (e.key === 'ArrowRight') {
        this.connection.socket.emit('UpdatePaddleInput', payload)
        this.arrowRight = false
      } else if (e.key === 'ArrowLeft') {
        this.connection.socket.emit('UpdatePaddleInput', payload)
        this.arrowLeft = false
      }
    },
    drawGame (ctx: CanvasRenderingContext2D, canvas: HTMLCanvasElement, state: CurrentGameState) {
      console.log('TESTING DRAWGAME')
      console.log(state)
      if (!state) {
        console.error('CurrentGameState is undefined')
        return
      }
      // Define an arrays for background gradients
      const gradientColors = ['red', 'blue', 'yellow', 'purple', 'orange']
      const gradient = ctx.createLinearGradient(0, 0, canvas.width, 0)
      gradientColors.forEach((color, index) => {
        gradient.addColorStop(index / (gradientColors.length - 1), color)
      })

      const stripeColors = ['black', 'white', 'black', 'white', 'black', 'white', 'black', 'white']
      const stripeGradient = ctx.createLinearGradient(0, 0, canvas.width, 0)
      stripeColors.forEach((color, index) => {
        const stop = index / (stripeColors.length - 1)
        stripeGradient.addColorStop(stop, color)
      })

      // draw background
      if (this.isBeBraveClicked) {
        ctx.fillStyle = gradient
      } else if (this.isZebraClicked) {
        ctx.fillStyle = stripeGradient
      } else {
        ctx.fillStyle = 'green'
      }
      ctx.fillRect(0, 0, canvas.width, canvas.height)

      // draw net
      for (let i = 0; i <= canvas.height; i += 15) {
        ctx.fillStyle = 'lightgreen'
        ctx.fillRect(canvas.width / 2 - 1.5, i, 3, 10)
      }

      // Draw a static ball shape (circle)
      ctx.fillStyle = 'white'
      ctx.beginPath()
      ctx.arc(state.ballCoords[0], state.ballCoords[1], state.ballRadius, 0, Math.PI * 2, false) // The full circle (0 to 2 * PI)
      ctx.closePath()
      ctx.fill()

      ctx.fillStyle = 'black'
      // draw the actual paddles based on their position
      if (state.leftPaddleCoords && state.leftPaddleCoords.length === 2) {
        console.log('draw left paddle')
        ctx.fillRect(state.leftPaddleCoords[0], state.leftPaddleCoords[1], state.leftPaddleWidth, state.leftPaddleHeight)
      }

      if (state.rightPaddleCoords && state.rightPaddleCoords.length === 2) {
        console.log('draw right paddle')
        ctx.fillRect(state.rightPaddleCoords[0], state.rightPaddleCoords[1], state.rightPaddleWidth, state.rightPaddleHeight)
      }
      // draw text player 1
      ctx.fillStyle = 'lightblue'
      ctx.font = '50px arial'
      ctx.fillText(this.namePlayer1, canvas.width / 4 - 100, canvas.height - 10)

      // draw text player 2
      ctx.fillStyle = 'lightblue'
      ctx.font = '50px arial'
      ctx.fillText(this.namePlayer2, canvas.width / 4 * 3 - 100, canvas.height - 10)
    },
    drawEndScreen (ctx: CanvasRenderingContext2D, canvas: HTMLCanvasElement, winningUser: string) {
      this.showCanvasAdd = true
      ctx.fillStyle = 'black'
      ctx.fillRect(0, 0, canvas.width, canvas.height)
      ctx.fillStyle = 'white'
      ctx.font = '50px arial'
      ctx.fillText(`${winningUser} won!`, canvas.width / 2 - 100, canvas.height / 2)
    }
  }
})
</script>
<style scoped>

.canvas-add{
  position: absolute;
  top: 100px; /* Adjust the value to move it down */
  left: 10px;
  width: 100%;
  height: 400px; /* Adjust the height as needed */
  z-index: 1;
}

.title {
  margin: 4rem 0; /* Increase top and bottom margin to create space */
  font-size: 24px;
  text-align: center;
  color: #71beba;
  margin-top: 2rem; /* Add top margin */
}

.gamecentre {
  display: flex;
  flex-direction: column;
  align-items: center; /* Align items horizontally in the center */
}

.gamecentre .custom-button {
  display: block;
  padding: 8px 18px; /* Increase the padding to make the button bigger */
  font-size: 15px; /* Increase the font size of the button text */
  font-weight: bold; /* Make the button text bold */
  margin-bottom: 50px; /* Add margin to separate the buttons vertically */
}

.gamecentre .orange-button {
  background-color: orange; /* Change color for orange buttons */
  color: white;
  font-weight: bold;
}

.gamecentre .orange-button:hover {
  background-color: darkorange; /* Change the background color to dark orange on hover */
}

.gamecentre .rainbow-button {
  background-image: linear-gradient(to right, red, orange, yellow, green, blue, indigo, violet);
  color: white;
  font-weight: bold;
}

.gamecentre .rainbow-button:hover {
  background-image: linear-gradient(to right, violet, indigo, blue, green, yellow, orange, red);
}

.gamecentre .zebra-button {
  background-image: linear-gradient(to right, black, white, black, white, black, white, black);
  color: white;
}

.gamecentre .zebra-button:hover {
  background-image: linear-gradient(to right, white, black, white, black, white, black, white);
  color: white;}

.gamecentre .essam-button {
  background-image: linear-gradient(to right, purple, blue, purple);
  color: white;
}

.gamecentre .essam-button:hover {
  background-image: linear-gradient(to right, blue, purple, blue);
  color: white;
}

.button-container {
  display: flex;
  flex-direction: column; /* Stack the buttons in a column layout */
  justify-content: center;

}

/* Add any necessary additional styles for the test screen */
</style>
