import BackButton from "../BackButton";
import Gallery from "../components/Gallery";

export default function Elites(): JSX.Element {
  return (
    <Gallery.Root>
      <Gallery.Text>
        <BackButton />
      </Gallery.Text>
      <Gallery.Title>200 Elite / 1 Hour route</Gallery.Title>
      <Gallery.Text>
        <p>Based on:</p>
        <ul>
          <li>
            2.4 Elite Farming Route from DrTraf (TrafDL#5886)
            https://imgur.com/a/CULV9MH
          </li>
          <li>200 elites route from Norre (SharedFate#3686)</li>
        </ul>
        <p>
          This route focuses on elites / min for those who would like to elite
          cap fast and / or are primarily interested in artifact fodder.
        </p>
        <p>
          In total this route nets 201 - 206+ elites (depending on leylines and
          the day in Tsurumi). The first half (ORANGE) of the route is ~106
          elites, and the second half (BLUE) is ~95 elites. In addition, the
          second half can be run on worlds that have already cleared the usual
          600s+200s route.
        </p>
        <p>Questions → enxi#0410</p>
      </Gallery.Text>
      <Gallery.Image src={`${process.env.PUBLIC_URL}/elites/Directions.jpg`} />
      <Gallery.Image
        src={`${process.env.PUBLIC_URL}/elites/Dragonspine-ish.jpg`}
      />
      <Gallery.Image src={`${process.env.PUBLIC_URL}/elites/Liyue-ish a.jpg`} />
      <Gallery.Image src={`${process.env.PUBLIC_URL}/elites/Liyue-ish b.jpg`} />
      <Gallery.Image
        src={`${process.env.PUBLIC_URL}/elites/Inazuma 600s200s a.jpg`}
      />
      <Gallery.Image
        src={`${process.env.PUBLIC_URL}/elites/Inazuma 600s200s b.jpg`}
      />
      <Gallery.Image
        src={`${process.env.PUBLIC_URL}/elites/Inazuma 600s200s c.jpg`}
      />
      <Gallery.Image
        src={`${process.env.PUBLIC_URL}/elites/Enkanomiya 600s200s.jpg`}
      />
      <Gallery.Image
        src={`${process.env.PUBLIC_URL}/elites/Enkanomiya Extra200s.jpg`}
      />
      <Gallery.Image
        src={`${process.env.PUBLIC_URL}/elites/Inazuma Extra200s a.jpg`}
      />
      <Gallery.Image
        src={`${process.env.PUBLIC_URL}/elites/Inazuma Extra200s b.jpg`}
      />
      <Gallery.Image
        src={`${process.env.PUBLIC_URL}/elites/Inazuma Extra200s c.jpg`}
      />
    </Gallery.Root>
  );
}
