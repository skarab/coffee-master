function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6402\" class=\"headerLeftMenuInActive\"><a id=\"aID6402\" href=\"#\" OnMouseOver=\"link('_dir','rigid_body0',this)\" class=\"leftMenuLinkHeadInActive\">rigid_body</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6395\" class=\"leftMenuInActive\"><a id=\"aID6395\" href=\"#\" OnMouseOver=\"link('_dir','box/box0',this)\" class=\"leftMenuLinkInActive\">box</a></div>\n");
document.write("<div id=\"divID6396\" class=\"leftMenuInActive\"><a id=\"aID6396\" href=\"#\" OnMouseOver=\"link('_dir','capsule/capsule0',this)\" class=\"leftMenuLinkInActive\">capsule</a></div>\n");
document.write("<div id=\"divID6397\" class=\"leftMenuInActive\"><a id=\"aID6397\" href=\"#\" OnMouseOver=\"link('_dir','chamfer_cylinder/chamfer_cylinder0',this)\" class=\"leftMenuLinkInActive\">chamfer_cylinder</a></div>\n");
document.write("<div id=\"divID6398\" class=\"leftMenuInActive\"><a id=\"aID6398\" href=\"#\" OnMouseOver=\"link('_dir','character/character0',this)\" class=\"leftMenuLinkInActive\">character</a></div>\n");
document.write("<div id=\"divID6399\" class=\"leftMenuInActive\"><a id=\"aID6399\" href=\"#\" OnMouseOver=\"link('_dir','cone/cone0',this)\" class=\"leftMenuLinkInActive\">cone</a></div>\n");
document.write("<div id=\"divID6400\" class=\"leftMenuInActive\"><a id=\"aID6400\" href=\"#\" OnMouseOver=\"link('_dir','cylinder/cylinder0',this)\" class=\"leftMenuLinkInActive\">cylinder</a></div>\n");
document.write("<div id=\"divID6401\" class=\"leftMenuInActive\"><a id=\"aID6401\" href=\"#\" OnMouseOver=\"link('_dir','mesh/mesh0',this)\" class=\"leftMenuLinkInActive\">mesh</a></div>\n");
document.write("<div id=\"divID6403\" class=\"leftMenuInActive\"><a id=\"aID6403\" href=\"#\" OnMouseOver=\"link('_dir','sphere/sphere0',this)\" class=\"leftMenuLinkInActive\">sphere</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID921\" class=\"leftMenuInActive\"><a id=\"aID921\" href=\"#\" OnMouseOver=\"link('_class','RigidBody14855',this)\" class=\"leftMenuLinkInActive\">RigidBody</a></div>\n");
document.write("<div id=\"divID922\" class=\"leftMenuInActive\"><a id=\"aID922\" href=\"#\" OnMouseOver=\"link('_class','RigidBodyShape14855',this)\" class=\"leftMenuLinkInActive\">RigidBodyShape</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
