function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6288\" class=\"headerLeftMenuInActive\"><a id=\"aID6288\" href=\"#\" OnMouseOver=\"link('_dir','vector0',this)\" class=\"leftMenuLinkHeadInActive\">vector</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID747\" class=\"leftMenuInActive\"><a id=\"aID747\" href=\"#\" OnMouseOver=\"link('_class','Vector239014',this)\" class=\"leftMenuLinkInActive\">Vector2</a></div>\n");
document.write("<div id=\"divID748\" class=\"leftMenuInActive\"><a id=\"aID748\" href=\"#\" OnMouseOver=\"link('_class','Vector2i39014',this)\" class=\"leftMenuLinkInActive\">Vector2i</a></div>\n");
document.write("<div id=\"divID749\" class=\"leftMenuInActive\"><a id=\"aID749\" href=\"#\" OnMouseOver=\"link('_class','Vector339014',this)\" class=\"leftMenuLinkInActive\">Vector3</a></div>\n");
document.write("<div id=\"divID750\" class=\"leftMenuInActive\"><a id=\"aID750\" href=\"#\" OnMouseOver=\"link('_class','Vector439014',this)\" class=\"leftMenuLinkInActive\">Vector4</a></div>\n");
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
