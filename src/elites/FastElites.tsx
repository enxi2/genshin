import BackButton from "../BackButton";
import Gallery from "../components/Gallery";

export default function FastElites(): JSX.Element {
  return (
    <Gallery.Root>
      <Gallery.Text>
        <BackButton />
      </Gallery.Text>
      <Gallery.Title>80-minute Elite Cap Route</Gallery.Title>
      <Gallery.Text>
        <p>
          This route consists of ~100 elites per world in ~18 minutes, allowing
          you to elite cap in 80 minutes with a 4-way trade.
        </p>
        <p>
          This will net you 5x600s + 95x200s per world, 88k mora for 4 worlds,
          so only worth it you're solely going for artifact fodder.
        </p>
      </Gallery.Text>
      <Gallery.Image
        src={`${process.env.PUBLIC_URL}/elites/fastcap/Inazuma a.jpg`}
      />
      <Gallery.Image
        src={`${process.env.PUBLIC_URL}/elites/fastcap/Inazuma b.jpg`}
      />
      <Gallery.Image
        src={`${process.env.PUBLIC_URL}/elites/fastcap/Enkanomiya.jpg`}
      />
    </Gallery.Root>
  );
}
