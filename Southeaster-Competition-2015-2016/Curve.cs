using UnityEngine;
using System.Collections;
using System.Runtime.InteropServices;
public class Curve : MonoBehaviour 
{
	private float degree;
	private float radius;
	private int size; //Total number of points in circle
	float theta_scale = 0.01f;  
	// Use this for initialization
	void Start () 
	{
		this.degree = 0;
		this.radius = 2;
	}
	LineRenderer lineRenderer;
	
	void Awake ()
	{       
		float sizeValue = (2.0f * Mathf.PI) / theta_scale; 
		size = (int)sizeValue;
		size++;
		lineRenderer = gameObject.AddComponent<LineRenderer>();
		lineRenderer.material = new Material(Shader.Find("Particles/Additive"));
		lineRenderer.SetWidth(0.02f, 0.02f); //thickness of line
		lineRenderer.SetVertexCount(size);      
	}
	// Update is called once per frame
	void Update ()
	{
		this.degree += 100.0f;

		float x = this.radius*Mathf.Cos(this.degree);
		float z = this.radius * Mathf.Sin (this.degree);

		this.transform.position = new Vector3 (x, this.transform.position.y, z);

		Vector3 pos;
		float theta = 0f;
		for(int i = 0; i < size; i++)
		{          
			theta += (2.0f * Mathf.PI * theta_scale);         
			 x = radius * Mathf.Cos(theta);
			 z = radius * Mathf.Sin(theta);          
			x += gameObject.transform.position.x;
			z += gameObject.transform.position.y;
			pos = new Vector3(x, z, 0);
			lineRenderer.SetPosition(i, pos);
		}
	}
}
