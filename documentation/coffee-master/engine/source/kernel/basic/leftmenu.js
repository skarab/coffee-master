function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6266\" class=\"headerLeftMenuInActive\"><a id=\"aID6266\" href=\"#\" OnMouseOver=\"link('_dir','basic0',this)\" class=\"leftMenuLinkHeadInActive\">basic</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6509\" class=\"leftMenuInActive\"><a id=\"aID6509\" href=\"#\" OnMouseOver=\"link('_dir','alpha/alpha0',this)\" class=\"leftMenuLinkInActive\">alpha</a></div>\n");
document.write("<div id=\"divID6268\" class=\"leftMenuInActive\"><a id=\"aID6268\" href=\"#\" OnMouseOver=\"link('_dir','container/container0',this)\" class=\"leftMenuLinkInActive\">container</a></div>\n");
document.write("<div id=\"divID6512\" class=\"leftMenuInActive\"><a id=\"aID6512\" href=\"#\" OnMouseOver=\"link('_dir','geometric/geometric0',this)\" class=\"leftMenuLinkInActive\">geometric</a></div>\n");
document.write("<div id=\"divID6502\" class=\"leftMenuInActive\"><a id=\"aID6502\" href=\"#\" OnMouseOver=\"link('_dir','hierarchy/hierarchy0',this)\" class=\"leftMenuLinkInActive\">hierarchy</a></div>\n");
document.write("<div id=\"divID6504\" class=\"leftMenuInActive\"><a id=\"aID6504\" href=\"#\" OnMouseOver=\"link('_dir','macros/macros0',this)\" class=\"leftMenuLinkInActive\">macros</a></div>\n");
document.write("<div id=\"divID6505\" class=\"leftMenuInActive\"><a id=\"aID6505\" href=\"#\" OnMouseOver=\"link('_dir','math/math0',this)\" class=\"leftMenuLinkInActive\">math</a></div>\n");
document.write("<div id=\"divID6289\" class=\"leftMenuInActive\"><a id=\"aID6289\" href=\"#\" OnMouseOver=\"link('_dir','property/property0',this)\" class=\"leftMenuLinkInActive\">property</a></div>\n");
document.write("<div id=\"divID6290\" class=\"leftMenuInActive\"><a id=\"aID6290\" href=\"#\" OnMouseOver=\"link('_dir','random/random0',this)\" class=\"leftMenuLinkInActive\">random</a></div>\n");
document.write("<div id=\"divID6506\" class=\"leftMenuInActive\"><a id=\"aID6506\" href=\"#\" OnMouseOver=\"link('_dir','raster/raster0',this)\" class=\"leftMenuLinkInActive\">raster</a></div>\n");
document.write("<div id=\"divID6293\" class=\"leftMenuInActive\"><a id=\"aID6293\" href=\"#\" OnMouseOver=\"link('_dir','time/time0',this)\" class=\"leftMenuLinkInActive\">time</a></div>\n");
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
